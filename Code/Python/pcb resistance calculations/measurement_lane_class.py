import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
import csv

### Classes ###
class measurment_lane:
    def __init__(self, topic):
        self.topic = topic
        #list order: timestamp, 12V, 3V3, AUX
        self.Measurement = [[],[[],[]],[[],[]],[[],[]]]

        #list order: 12V(timestamp, volt,curr,pow), 3v3(timestamp, volt,curr,pow), AUX(timestamp, volt,curr,pow)
        self.Measurement_float= [ [[],[],[],[]] , [[],[],[],[]] , [[],[],[],[]] ]
        self.quantisierung = [[[],[]],[[],[]],[[],[]]]
        self.time =[[],[],[]]
        self.to_Database = []
        self.msg_amt = 0
        # self.fig, self.axes = plt.subplots(2, 3, figsize=(12, 8))
        self.len_before = 0
        # current  12V, 3V3, AUX
        self.current = [[],[],[]]
  
    def plot_12V(self):
        fi1, axes = plt.subplots(2, 1, figsize=(12, 8),num = self.topic)
        axes[0].plot(self.Measurement_float[0][0], self.Measurement_float[0][1], linestyle = 'None', marker = 'o', color='blue')
        axes[0].set_title('Bus Volt 12V')
        axes[0].set_xlabel('Time [s]')  # X-axis title with units
        axes[0].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0].grid(True)
        # figaxes = plt.subplots(1,1 , figsize=(12, 8),num = self.topic)
        axes[1].plot(self.Measurement_float[0][0], self.Measurement_float[0][2], linestyle = 'None', marker = 'o', color='red')
        axes[1].set_title('Current 12V')
        axes[1].set_xlabel('Time [s]')  # X-axis title with units
        axes[1].set_ylabel('Current [A]')         # Y-axis title
        axes[1].grid(True)

        plt.show

        # Save the plot automatically with a specific filename and format
        plt.savefig('sine_wave.png', format='png')
    

    def save_12V(self):
        fi1, axes = plt.subplots(2, 1, figsize=(12, 8),num = self.topic)
        axes[0].plot(self.Measurement_float[0][0], self.Measurement_float[0][1], linestyle = 'None', marker = 'o', color='blue')
        axes[0].set_title('Bus Volt 12V')
        axes[0].set_xlabel('Time [s]')  # X-axis title with units
        axes[0].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0].grid(True)
        # figaxes = plt.subplots(1,1 , figsize=(12, 8),num = self.topic)
        axes[1].plot(self.Measurement_float[0][0], self.Measurement_float[0][2], linestyle = 'None', marker = 'o', color='red')
        axes[1].set_title('Current 12V')
        axes[1].set_xlabel('Time [s]')  # X-axis title with units
        axes[1].set_ylabel('Current [A]')         # Y-axis title
        axes[1].grid(True)



        plt.show

 

    def save_in_csv_single_bus(self, dateiname, index):

        length = len(self.Measurement_float[index][0])
        with open(dateiname + ".csv", 'w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['Zeit[s]','Spannung[V]','Strom[A]', 'Power[W]'])
            for i in range(length):
                    csv_writer.writerow([self.Measurement_float[index][0][i],self.Measurement_float[index][1][i],self.Measurement_float[index][2][i], self.Measurement_float[index][3][i]])

        print("Data have been saved in", dateiname)

        fi1, axes = plt.subplots(2, 1, figsize=(12, 8),num = self.topic)
        axes[0].plot(self.Measurement_float[index][0][:length], self.Measurement_float[index][1][:length], linestyle = 'None', marker = 'o', color='blue')
        axes[0].set_title('Bus Volt')
        axes[0].set_xlabel('Time [s]')  # X-axis title with units
        axes[0].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0].grid(True)
        # figaxes = plt.subplots(1,1 , figsize=(12, 8),num = self.topic)
        axes[1].plot(self.Measurement_float[index][0][:length], self.Measurement_float[index][2][:length], linestyle = 'None', marker = 'o', color='red')
        axes[1].set_title('Current')
        axes[1].set_xlabel('Time [s]')  # X-axis title with units
        axes[1].set_ylabel('Current [A]')         # Y-axis title
        axes[1].grid(True)

        plt.show

        # Save the plot automatically with a specific filename and format
        plt.savefig(dateiname + ".png", format='png')
    





    # def plot_float_current(self):
        
    #     y_lim_shunt = [-0.01,0.09]
    #     fig, axes = plt.subplots(3, 3, figsize=(12, 8),num = self.topic)

    #     axes[0, 0].plot(self.Measurement_float[0][0], self.Measurement_float[0][1], linestyle = 'None', marker = 'o', color='blue')
    #     axes[0, 0].set_title('Bus Volt 12V')
    #     axes[0, 0].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[0, 0].set_ylabel('Voltage [V]')         # Y-axis title
    #     axes[0, 0].grid(True)

    #     axes[0, 1].plot(self.Measurement_float[1][0], self.Measurement_float[1][1],  linestyle = 'None', marker = 'o', color='blue')
    #     axes[0, 1].set_title('Bus Volt 3V3')
    #     axes[0, 1].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[0, 1].set_ylabel('Voltage [V]')         # Y-axis title
    #     axes[0, 1].grid(True)

    #     axes[0, 2].plot(self.Measurement_float[2][0], self.Measurement_float[2][1], linestyle = 'None', marker = 'o', color='blue')
    #     axes[0, 2].set_title('Bus Volt AUX')
    #     axes[0, 2].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[0, 2].set_ylabel('Voltage [V]')         # Y-axis title
    #     axes[0, 2].grid(True)

        


    #     #plot current 
    #     axes[2, 0].plot(time, current12V,  linestyle = 'None', marker = 'o', color='red')
    #     axes[2, 0].set_title('Current 12V')
    #     axes[2, 0].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[2, 0].set_ylabel('Current [A]')         # Y-axis title
    #     axes[2, 0].grid(True)

    #     axes[2, 1].plot(time, current3V3,  linestyle = 'None', marker = 'o', color='red')
    #     axes[2, 1].set_title('Current 3V3')
    #     axes[2, 1].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[2, 1].set_ylabel('Current [A]')         # Y-axis title
    #     axes[2, 1].grid(True)

    #     axes[2, 2].plot(time, currentAUX,  linestyle = 'None', marker = 'o', color='red')
    #     axes[2, 2].set_title('Current AUX')
    #     axes[2, 2].set_xlabel('Time [s]')  # X-axis title with units
    #     axes[2, 2].set_ylabel('Current [A]')         # Y-axis title
    #     axes[2, 2].grid(True)
    

    def plot_data(self):

        
        length = len(self.time)
       


        # if (length - self.len_before) > 1000: 
        time = self.time[:length]
        bus_volt12      = self.Measurement[1][0][:length]
        shunt_volt12    = self.Measurement[1][1][:length]
        current12V      = self.current[0][:length]
        bus_volt3V3     = self.Measurement[2][0][:length]
        shunt_volt3V3   = self.Measurement[2][1][:length]
        current3V3      = self.current[1][:length]
        bus_voltAUX     = self.Measurement[3][0][:length]
        shunt_voltAUX   = self.Measurement[3][1][:length]
        currentAUX      = self.current[2][:length]
        


        #Plot
        y_lim_shunt = [-0.01,0.09]
        fig, axes = plt.subplots(3, 3, figsize=(12, 8),num = self.topic)
        axes[0, 0].plot(time, bus_volt12, linestyle = 'None', marker = 'o', color='blue')
        axes[0, 0].set_title('Bus Volt 12V')
        axes[0, 0].set_xlabel('Time [s]')  # X-axis title with units
        axes[0, 0].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0, 0].grid(True)

        axes[1, 0].plot(time, shunt_volt12,  linestyle = 'None', marker = 'o', color='green')
        axes[1, 0].set_title('Shunt Volt 12V')
        axes[1, 0].set_xlabel('Time [s]')  # X-axis title with units
        axes[1, 0].set_ylabel('Voltage [V]')         # Y-axis title
        axes[1, 0].set_ylim(y_lim_shunt)
        axes[1, 0].grid(True)

        axes[0, 1].plot(time, bus_volt3V3,  linestyle = 'None', marker = 'o', color='blue')
        axes[0, 1].set_title('Bus Volt 3V3')
        axes[0, 1].set_xlabel('Time [s]')  # X-axis title with units
        axes[0, 1].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0, 1].grid(True)

        axes[1, 1].plot(time, shunt_volt3V3,  linestyle = 'None', marker = 'o', color='green')
        axes[1, 1].set_title('Shunt Volt 3V3')
        axes[1, 1].set_xlabel('Time [s]')  # X-axis title with units
        axes[1, 1].set_ylabel('Voltage [V]')         # Y-axis title
        axes[1, 1].set_ylim(y_lim_shunt)
        axes[1, 1].grid(True)

        axes[0, 2].plot(time, bus_voltAUX,  linestyle = 'None', marker = 'o', color='blue')
        axes[0, 2].set_title('Bus Volt AUX')
        axes[0, 2].set_xlabel('Time [s]')  # X-axis title with units
        axes[0, 2].set_ylabel('Voltage [V]')         # Y-axis title
        axes[0, 2].grid(True)

        axes[1, 2].plot(time, shunt_voltAUX,  linestyle = 'None', marker = 'o', color='green')
        axes[1, 2].set_title('Shunt Volt AUX')
        axes[1, 2].set_xlabel('Time [s]')  # X-axis title with units
        axes[1, 2].set_ylabel('Voltage [V]')         # Y-axis title
        axes[1, 2].set_ylim(y_lim_shunt)
        axes[1, 2].grid(True)

        axes[2, 0].plot(time, current12V,  linestyle = 'None', marker = 'o', color='red')
        axes[2, 0].set_title('Current 12V')
        axes[2, 0].set_xlabel('Time [s]')  # X-axis title with units
        axes[2, 0].set_ylabel('Current [A]')         # Y-axis title
        axes[2, 0].grid(True)


        axes[2, 1].plot(time, current3V3,  linestyle = 'None', marker = 'o', color='red')
        axes[2, 1].set_title('Current 3V3')
        axes[2, 1].set_xlabel('Time [s]')  # X-axis title with units
        axes[2, 1].set_ylabel('Current [A]')         # Y-axis title
        axes[2, 1].grid(True)

        axes[2, 2].plot(time, currentAUX,  linestyle = 'None', marker = 'o', color='red')
        axes[2, 2].set_title('Current AUX')
        axes[2, 2].set_xlabel('Time [s]')  # X-axis title with units
        axes[2, 2].set_ylabel('Current [A]')         # Y-axis title
        axes[2, 2].grid(True)

        self.len_before = length

        # plt.get_current_fig_manager().full_screen_toggle()
        # 

    
  
    

    global ani
    def live_plot(self):
        global ani
        ani = FuncAnimation(self.fig, self.plot_data, interval=10000)
        # plt.close(fig= )
        print(plt.get_fignums())
        plt.close(2)
        plt.close(3)
        # plt.get_current_fig_manager().full_screen_toggle()
        
        plt.show()
        # return ani