
### Imports ###

import paho.mqtt.client as mqtt
from datetime import datetime as dt
from measurement_lane_class import  measurment_lane
import matplotlib.pyplot as plt
from time import sleep

    

### Variables ###
#topic strings, 
measurment_topics = ["PCIe1", "PCIe2", "SUPP"]
config_topics = ["PMS_Config"]
subtopics_config = ["GO","UseCase"]

# list to store all constructed measurment_lane class objects for better access 
topic_class_list = []

# Liste zum Speichern der empfangenen Nachrichten als Hex-Werte
received_messages_hex = []
received_messages_section = []
timestamps_difference = []
ts_before = 0
sekunden_list = []
millisekunden_list = []

# #list order: timestamp, 12V, 3V3, AUX
# Measurement = [[],[[],[]],[[],[]],[[],[]]]
# to_Database = []

#incoming meassage counter for each topic
# msg_amt = [[],[],[]] 

### Functions ####

#chunkiung data function 
def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]




# Callback, das aufgerufen wird, wenn eine Verbindung zum Broker hergestellt wurde
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Verbindung hergestellt: Verbindungstyp =", rc)
        # Hier könntest du dich für Themen anmelden oder andere Aktionen durchführen
    else:
        print("Verbindung fehlgeschlagen: Verbindungstyp =", rc)


# Callback, das aufgerufen wird, wenn eine Nachricht empfangen wurde
def on_message(client, userdata, message):
    global msg_amt
    global Measurement
    global timestamps_difference
    global ts_before
    
    # empty  class object
    store_object = measurment_lane("")

    #incoming topic string, 
    incoming_topic = message.topic

    

    # Vergleiche das eingehende Thema mit den Themen der MeasurementLane-Objekte
    for lane in topic_class_list:
        if incoming_topic == lane.topic:
            store_object = lane
            break


    # print(store_object.topic) 
    #increase meassage counter for object
    store_object.msg_amt += 1
    
    # prepare meassage to be handled
    hex_value = message.payload.hex()
    received_messages_hex.append(hex_value)

    #treat NUXI problem, change endian
    ba = bytearray.fromhex(hex_value)
    ba.reverse()
    hex_value = (ba.hex()[::-1])
    

    # sepperate the data package
    # number of packages inside the the chunk
    DATA_CHUNKING = 6
    sliced_data = chunks(hex_value, 36)
    
    # itterate over each data package
    for k,data in enumerate(sliced_data):
        
        

        # raw measurement data are contained in the first 12 Byte
        first_12_bytes = (data[0:24] )[::-1] # Ersten 12 Byte

        #Get raw measurement data from mqtt msg
        bus_volt = [first_12_bytes[20:24],first_12_bytes[16:20],first_12_bytes[12:16]]
        shunt_volt = [first_12_bytes[8:12],first_12_bytes[4:8],first_12_bytes[0:4]]

        #swap bytes of raw measurement data, still because of endian
        bus_volt = [bytearray.fromhex(i)[::-1].hex() for i in bus_volt]
        shunt_volt = [bytearray.fromhex(i)[::-1].hex() for i in shunt_volt]

    # timestamp
        # get raw timestamp data
        last_6_bytes = data[24:36]  # Letzten 6 Byte, 12 zeichen
        sekunden = int((last_6_bytes[0:8])[::-1],16)
        millisekunden = int((last_6_bytes[8:12])[::-1],16)

        #store seperated time values for better plotting
        sekunden_list.append(sekunden)
        millisekunden_list.append(millisekunden)


        # get whole timestamp 
        milli_res = 1/10000
        ts = float(sekunden) + float(millisekunden)*milli_res 
        



    #Data processing

        # raw to real value coneffiecients
        bus_LSB = 1.25e-3 
        shunt_LSB = 25e-7 
        shunt_res = [10e-3, 25e-3]
        # get real measurement value as floating point number
        for j in range(len(bus_volt)):
            bus_volt[j] = int(bus_volt[j],16) * bus_LSB
            shunt_volt[j] = int(shunt_volt[j],16) * shunt_LSB
            
        #calculate time differenece between two time stamps    
        try:
            timestamps_difference.append( ts - ts_before )
            ts_before = ts
        except:
            len(Measurement) <= 1
        
        #store measurement data into lists for better handling while ploting
        #get passed time since start

        if store_object.msg_amt > 1:
            start_time = store_object.Measurement[0][0]
            store_object.time.append(ts - start_time)
        #store measurementdata for ploting
        #12v Current 0
        store_object.current[0].append(float(shunt_volt[0])/ shunt_res[0]) 
                                      
        #3v3 current
        store_object.current[1].append(float(shunt_volt[1])/ shunt_res[1])
        #AUX current
        store_object.current[2].append(float(shunt_volt[2])/ shunt_res[1])
        
        store_object.Measurement[0].append(ts)
        store_object.Measurement[1][0].append(bus_volt[0])
        store_object.Measurement[1][1].append(shunt_volt[0])
        store_object.Measurement[2][0].append(bus_volt[1])
        store_object.Measurement[2][1].append(shunt_volt[1])
        store_object.Measurement[3][0].append(bus_volt[2])
        store_object.Measurement[3][1].append(shunt_volt[2])

        #store measurment data in a way which is better for transfering it into the database
        store_object.to_Database.append( (ts,
                            (bus_volt[0],shunt_volt[0]),
                            (bus_volt[1],shunt_volt[1]),
                            (bus_volt[2],shunt_volt[2])))

            # print(Measurement)
    # if store_object.msg_amt%1000 == 0:
        # print("{} msg amount:{}".format(store_object.topic,store_object.msg_amt))




# Erzeuge einen MQTT-Client
client = mqtt.Client(client_id="transformscript")

# Setze die Callbacks
client.on_connect = on_connect
client.on_message = on_message

# Setze die Verbindungsinformationen (Broker-Adresse und Port)
# broker_address = "localhost"  # Beispiel-Broker
port = 1883  # Standard MQTT-Port
broker_address = "192.168.1.24"

# Verbinde zum Broker
client.connect(broker_address, port, keepalive=60)

# Starte den MQTT-Loop, um Nachrichten zu verarbeiten
client.loop_start()

# Subscribe for topics
for topic in measurment_topics:
    topic_class_list.append(measurment_lane(topic)) 
    client.subscribe(topic)





DATA_MSG_THRESHHOLD = 1000
# plt.ion()   



# topic_class_list[0].live_plot() 

# topic_class_list[0].plot_data(1)
# plt.show()
sleep(30)
try:
    while True:
        # pass
      
        # topic_class_list[0].plot_data()
        topic_class_list[1].plot_data() 
        plt.show(block = None)    
        sleep(5)
        # plt.close()
except KeyboardInterrupt:
    # [plt.close(topic_class.fig) for topic_class in topic_class_list]
    # Bei Tastenunterbrechung beenden
    client.disconnect()
    client.loop_stop()





