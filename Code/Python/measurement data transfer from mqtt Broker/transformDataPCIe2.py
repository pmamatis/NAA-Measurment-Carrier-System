import paho.mqtt.client as mqtt
from datetime import datetime as dt
import matplotlib.pyplot as plt





#chunkiung data function 
def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


# Liste zum Speichern der empfangenen Nachrichten als Hex-Werte
received_messages_hex = []
received_messages_section = []
timestamps_difference = []
ts_before = 0
sekunden_list = []
millisekunden_list = []

#list order: timestamp, 12V, 3V3, AUX
Measurement = [[],[[],[]],[[],[]],[[],[]]]
to_Database = []

# Callback, das aufgerufen wird, wenn eine Verbindung zum Broker hergestellt wurde
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Verbindung hergestellt: Verbindungstyp =", rc)
        # Hier könntest du dich für Themen anmelden oder andere Aktionen durchführen
    else:
        print("Verbindung fehlgeschlagen: Verbindungstyp =", rc)


msg_amt = 0
# Callback, das aufgerufen wird, wenn eine Nachricht empfangen wurde
def on_message(client, userdata, message):
    global msg_amt
    global Measurement
    global timestamps_difference
    global ts_before

    #immer noch ein str
    hex_value = message.payload.hex()
    received_messages_hex.append(hex_value)
    msg_amt += 1
    # print("Nachricht empfangen auf Topic:", message.topic)
    # print(hex_value)

    #treat NUXI problem, change endian
    ba = bytearray.fromhex(hex_value)
 
    ba.reverse()
    hex_value = (ba.hex()[::-1])
    

    # # unterteile Nachricht in einzelene Daten pakete
    DATA_CHUNKING = 6
    sliced_data = chunks(hex_value, 36)
    
    for k,data in enumerate(sliced_data):
        
     

        # raw measurement data
        # first_12_bytes = (data[0:24] ) # Ersten 12 Byte
        first_12_bytes = (data[0:24] )[::-1] # Ersten 12 Byte

        #Get raw measurement data from mqtt msg
        bus_volt = [first_12_bytes[20:24],first_12_bytes[16:20],first_12_bytes[12:16]]
        shunt_volt = [first_12_bytes[8:12],first_12_bytes[4:8],first_12_bytes[0:4]]

        #swap bytes of raw measurement data, because of endian
        bus_volt = [bytearray.fromhex(i)[::-1].hex() for i in bus_volt]
        shunt_volt = [bytearray.fromhex(i)[::-1].hex() for i in shunt_volt]


        # get raw timestamp data
        last_6_bytes = data[24:36]  # Letzten 6 Byte, 12 zeichen
        sekunden = int((last_6_bytes[0:8])[::-1],16)
        millisekunden = int((last_6_bytes[8:12])[::-1],16)
        # print(first_12_bytes)
        sekunden_list.append(sekunden)
        millisekunden_list.append(millisekunden)
    #timestamp
        milli_res = 1/10000
        ts = float(sekunden) + float(millisekunden)*milli_res 
        # ts = float(millisekunden)#*milli_res 
        



    #Data processing
        bus_LSB = 1.25e-3 
        shunt_LSB = 25e-7 
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
        Measurement[0].append(ts)
        Measurement[1][0].append(bus_volt[0])
        Measurement[1][1].append(shunt_volt[0])
        Measurement[2][0].append(bus_volt[1])
        Measurement[2][1].append(shunt_volt[1])
        Measurement[3][0].append(bus_volt[2])
        Measurement[3][1].append(shunt_volt[2])

        #store measurment data in a way which is beter for transfering it into the database
        to_Database.append( (ts,
                            (bus_volt[0],shunt_volt[0]),
                            (bus_volt[1],shunt_volt[1]),
                            (bus_volt[2],shunt_volt[2])))
        # print(Measurement)
    if msg_amt%1000 == 0:
        print(msg_amt)



# Erzeuge einen MQTT-Client
client = mqtt.Client(client_id="transformscriptPCIe2")

# Setze die Callbacks
client.on_connect = on_connect
client.on_message = on_message

# Setze die Verbindungsinformationen (Broker-Adresse und Port)
broker_address = "localhost"  # Beispiel-Broker
port = 1883  # Standard MQTT-Port

# Verbinde zum Broker
client.connect(broker_address, port, keepalive=60)

# Starte den MQTT-Loop, um Nachrichten zu verarbeiten
client.loop_start()

# Subscribe dich für ein Topic
topic = "PCIe2"
client.subscribe(topic)




DATA_MSG_THRESHHOLD = 1000


try:
    while True:
        if True:
            #Data  Evaluation
            if msg_amt >= DATA_MSG_THRESHHOLD:
                # Plot für bus_volt

                time = Measurement[0]
                
                if True:
                #bus voltage 
                    fig1, ax = plt.subplots(figsize=(8, 5))
                    plt.plot(time, Measurement[1][0], marker='o', label='12V')
                    plt.plot(time, Measurement[2][0], marker='o', label='3V3')
                    plt.plot(time, Measurement[3][0], marker='o', label='AUX')
                    plt.xlabel('ts')
                    plt.ylabel('bus_volt')
                    plt.title('Bus Voltage PCIe2')
                    plt.legend()
                    plt.grid(True)

                if True:
                    # Plot für shunt_volt
                    fig2, ax = plt.subplots(figsize=(8, 5))
                    plt.plot(time, Measurement[1][1], marker='o', label='12V')
                    plt.plot(time, Measurement[2][1], marker='o', label='3V3')
                    plt.plot(time, Measurement[3][1], marker='o', label='AUX')
                    plt.xlabel('ts')
                    plt.ylabel('shunt_volt')
                    plt.title('Shunt Voltages PCIe2')
                    plt.legend()
                    plt.grid(True)

                if False:

                    len_x =len(timestamps_difference) 
                    timestamps_difference_plot = timestamps_difference[1:len(timestamps_difference)]
                    len_x = len(timestamps_difference_plot)

                    #Histogramm
                    fig32, ax = plt.subplots(figsize=(8, 5))
                    bins = [-1,0,0.0009,0.0015,0.0025,0.0035,1]
                    plt.hist(timestamps_difference_plot, bins=bins, edgecolor='black')  # 'bins' gibt die Anzahl der Bins im Histogramm an
                    plt.xlabel('Werte')
                    plt.ylabel('Häufigkeit')
                    plt.title('Histogramm')
                    
                    fig3, ax = plt.subplots(figsize=(8, 5))
                    plt.plot(range(len_x), timestamps_difference_plot, marker='o', label='len ={} '.format(len_x))
                    plt.xlabel('number')
                    plt.ylabel('timestamp diffrence [s]')
                    plt.title('timestamp continuity')
                    plt.legend()
                    plt.grid(True)
                
                if False:
                    
                    fig4, ax = plt.subplots(figsize=(8, 5))
                    len_time = len(time)
                    time_plot = time[0:len_time]
                    plt.plot(range(len_time),time_plot, marker='o', label='12V')
                    plt.xlabel('number')
                    plt.ylabel('timestamp[s]')
                    plt.title('timestamp') 
                    plt.legend()
                    plt.grid(True)

                if False:
                    fig5, ax = plt.subplots(figsize=(8, 5))
                    plt.plot(range(len(sekunden_list)),sekunden_list, marker='o', label='sekunden')
                    plt.xlabel('number')
                    plt.ylabel('sekunden [s]')
                    plt.title('Sekunden')
                    plt.legend()
                    plt.grid(True)
                if False:
                    fig6, ax = plt.subplots(figsize=(8, 5))
                    plt.plot(range(len(millisekunden_list)),millisekunden_list, marker='o', label='sekunden')
                    plt.xlabel('number')
                    plt.ylabel('millisekunden [µs]')
                    plt.title('1/10 ms-Sekunden')
                    plt.legend()
                    plt.grid(True)
                if False:
                    #Sekunden und micro Sekunden übereinander
                    len_sec = len(sekunden_list)
                    sekunden_plot = sekunden_list[0:len_sec]

                    len_msec = len(millisekunden_list)
                    millisekunden_plot = millisekunden_list[0:len_msec]                    



                    fig, ax1 = plt.subplots()

                    # Erstelle das erste Plotobjekt für die erste Y-Achse (links)
                    ax1.plot(range(len_sec), sekunden_plot, 'b-',marker='o')
                    ax1.set_xlabel('Index')
                    ax1.set_ylabel('Sekunden in s', color='b')
                    ax1.tick_params('y', colors='b')

                    # Erstelle einen zweiten Y-Achsen-Plotobjekt (rechts)
                    ax2 = ax1.twinx()
                    ax2.plot(range(len_msec), millisekunden_plot, 'r-',marker='o')
                    ax2.set_ylabel('microseconds in 100µs', color='r')
                    ax2.tick_params('y', colors='r')
                    plt.grid(True)
                    plt.title('Sekunden und MicroSekunden')
                    plt.show()

                 
            plt.show()    


        

    
        
        pass
except KeyboardInterrupt:
    # Bei Tastenunterbrechung beenden
    client.disconnect()
    client.loop_stop()