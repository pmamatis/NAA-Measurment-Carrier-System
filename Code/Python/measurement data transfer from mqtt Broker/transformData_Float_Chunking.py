
### Imports ###

import paho.mqtt.client as mqtt
from datetime import datetime as dt
from measurement_lane_class import  measurment_lane
import matplotlib.pyplot as plt
from time import sleep
import struct




### Variables ###
#topic strings, 
measurment_topics = ["PCIe1", "PCIe2", "SUPP"]
rail_topics = ["12V", "3V3", "AUX"]
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
    MEASUREMENT_DATA_SIZE_BYTES = 44
    MEASUREMENT_VALUE_SIZE = 8
    # empty  class object
    store_object = measurment_lane("")

    #incoming topic string, 
    incoming_topic = message.topic
    # print(incoming_topic)
    

    # Vergleiche das eingehende Thema mit den Themen der MeasurementLane-Objekte
    for lane in topic_class_list:
        if lane.topic in incoming_topic:
            store_object = lane
            # print(lane.topic)
            break


    # print(store_object.topic) 
    #increase meassage counter for object
    store_object.msg_amt += 1
    
    # prepare meassage to be handled

    hex_value = message.payload.hex()
    received_messages_hex.append(hex_value)

    ba = bytearray.fromhex(hex_value)


    #treat NUXI problem, change endian


    #turn byte array so inside the  4-Byte values is the right order, but the order of the values itself is wrong 
    ba.reverse()
    hex_value = (ba.hex()[::-1])



    #convert the number of chunks to chunking size in bytes
    chunking_size = int((len(hex_value)/3))

    if store_object.msg_amt%1000 == 0:
            print("{} msg amount:{}".format(store_object.topic,store_object.msg_amt))       

    sliced_measurment_data = chunks(hex_value,chunking_size) 
    for measurement_data in sliced_measurment_data:

        timestamp_raw = [measurement_data[:MEASUREMENT_VALUE_SIZE],measurement_data[MEASUREMENT_VALUE_SIZE: MEASUREMENT_VALUE_SIZE*2]]
        bus_volt =  [measurement_data[2*MEASUREMENT_VALUE_SIZE:3*MEASUREMENT_VALUE_SIZE],measurement_data[3*MEASUREMENT_VALUE_SIZE:4*MEASUREMENT_VALUE_SIZE],measurement_data[MEASUREMENT_VALUE_SIZE*4:MEASUREMENT_VALUE_SIZE*5]]
        current =   [measurement_data[5*MEASUREMENT_VALUE_SIZE:6*MEASUREMENT_VALUE_SIZE],measurement_data[6*MEASUREMENT_VALUE_SIZE:7*MEASUREMENT_VALUE_SIZE],measurement_data[MEASUREMENT_VALUE_SIZE*7:MEASUREMENT_VALUE_SIZE*8]]
        power =     [measurement_data[8*MEASUREMENT_VALUE_SIZE:9*MEASUREMENT_VALUE_SIZE],measurement_data[9*MEASUREMENT_VALUE_SIZE:10*MEASUREMENT_VALUE_SIZE],measurement_data[MEASUREMENT_VALUE_SIZE*10:MEASUREMENT_VALUE_SIZE*11]]


        # convert hex to int
        sekunden =  int(timestamp_raw[0][::-1],16)
        u_sekunden = int(timestamp_raw[1][::-1] ,16)
        timestamp = sekunden + u_sekunden*1e-6


      

        for i in range(3):
            #convert data
            bus_volt[i] = struct.unpack('!f', bytes.fromhex((bus_volt[i][::-1])))[0] 
            current[i] = struct.unpack('!f', bytes.fromhex((current[i][::-1])))[0] 
            power[i] = struct.unpack('!f', bytes.fromhex((power[i][::-1])))[0] 

            #store data
            store_object.Measurement_float[i][0].append(timestamp)
            store_object.Measurement_float[i][1].append(bus_volt[i])                                                  
            store_object.Measurement_float[i][2].append(current[i])                                                  
            store_object.Measurement_float[i][3].append(power[i]) 
            try:
                store_object.time[i].append(timestamp -store_object.Measurement_float[i][0][0])
            except:
                 store_object.msg_amt < 1
     
       
                                 
        





#MAIN
# Erzeuge einen MQTT-Client
client = mqtt.Client(client_id="transformscript")

# Setze die Callbacks
client.on_connect = on_connect
client.on_message = on_message

# Setze die Verbindungsinformationen (Broker-Adresse und Port)
# broker_address = "localhost"  # Beispiel-Broker
port = 1883  # Standard MQTT-Port
broker_address = "172.24.10.168"

# Verbinde zum Broker
client.connect(broker_address, port, keepalive=60)

# Starte den MQTT-Loop, um Nachrichten zu verarbeiten
client.loop_start()

# Subscribe for topics
for topic in measurment_topics:
    topic_class_list.append(measurment_lane(topic))
    topic = topic + "/#"
    # print(topic)
    client.subscribe(topic)






DATA_MSG_THRESHHOLD = 1000
# plt.ion()   



# topic_class_list[0].live_plot() 

# topic_class_list[0].plot_data(1)
# plt.show()
# sleep(3)
sleep(6000)
# topic_class_list[0].save_in_csv_single_bus("Offset_pcie1_Drat_Kurschluss_mitBUsSpannungundLast",0)
topic_class_list[0].save_in_csv_single_bus("Streuung 5A5",0)
print("measurement read!")
# conv_time_sweep(topic_class_list[1].Measurement_float[0])
try:
    while True:
        # pass
      
        # topic_class_list[0].plot_12V()
        # topic_class_list[1].plot_12V()
      

        # topic_class_list[1].conv_time_sweep()
        plt.show(block = None)
        sleep(10)
        # plt.close()
except KeyboardInterrupt:
    # [plt.close(topic_class.fig) for topic_class in topic_class_list]
    # Bei Tastenunterbrechung beenden
    client.disconnect()
    client.loop_stop()





