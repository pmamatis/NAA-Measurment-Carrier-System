import helper as help
import numpy as np
from scipy import stats as st
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
from Messdaten_class import Auswertung_t
import statsmodels.api as sm
import statistics 
#Plote die Histogramme der Messdaten nach jeder Mittelwertbildung



def Histogramm(Messung):
    LSB_Strom = 0.25e-3
    Daten = Messung.Strom.rohdaten    

    #Häufigkeit der einzelnen Werte
    Daten.sort()
    Bins,Haeufigkeit = help.calculate_frequencies(Daten)



    # #Weite der einzelnen Bins
    # Weite_Strom = 0.25e-3
    # Weite_Spannung = 1.25e-3

    # plt.bar(Bins_Strom[0].sort)
    plt.bar(Bins,Haeufigkeit, width = LSB_Strom, edgecolor='black')
    
    # plt.hist(Messung.Strom.rohdaten, bins=Bins_Strom[0], color='skyblue', edgecolor='black')
    # plt.set_ylabel('Anzahl')
    plt.grid(True) 

    # plt.show()
   
def Normalverteilungstest(Messung,figname,line = False):
    """
    Erstellt einen Plot, bestehend aus Messdatenplot, Histogramm und QQ-Plot
    mit dem visuel betsimmmt werden kann ob die Messung Normalverteilt ist


    """

    # Messung = MC.Auswertung_t('204µs',204,'/media/paul/LINUX_MEM/Fraunhofer/GIT Repos/Master Thesis/Software/Python Skript/Conv_time_sweep/first_measurement/204u.csv',5)


    #Anzahl an Bins berechnen für die Histogramme
    Bins_Strom = [\
                len(set(Messung.Strom.rohdaten)),\
                len(set(Messung.Strom.mittelwerte[0])),\
                len(set(Messung.Strom.mittelwerte[1]))]
    Bins_Spannung= [\
                len(set(Messung.Spannung.rohdaten)),\
                len(set(Messung.Spannung.mittelwerte[0])),\
                len(set(Messung.Spannung.mittelwerte[1]))]

    #Häufigkeit der einzelnen Werte
    Häufigkeit_Strom = np.histogram(Messung.Strom.rohdaten)
    Häufigkeit_Spannung = np.histogram(Messung.Spannung.rohdaten)
    
    #Weite der einzelnen Bins
    Weite_Strom = 0.25e-3
    Weite_Spannung = 1.25e-3


    #Normalverteilungstest

    #Anzahl Reihen und Zeilen im PLot
    
    nrows = 3
    ncols = 3
    if (Messung.k == 0):
        ncols = 2
    
    #PLot größe skalieren
    k = 5

    #Plot Strom
    if (1):
        # plt.figure()
        plt.rcParams.update({'font.size': 20})

     
        fig, axes = plt.subplots(nrows,ncols,figsize=(k * 7, k * 10/4))
        fig.canvas.manager.set_window_title(Messung.name)

        linestyle = 'None'
        if line:
            linestyle = 'solid'        

        #Messdaten Plot
        #rohdaten
        if (0):
            # X-Achse mit index
            axes[0,0].plot(range(len(Messung.Strom.rohdaten)),Messung.Strom.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='red')
        else:
            # X-Achse mit Zeitstempel
            axes[0,0].plot(Messung.Zeit,Messung.Strom.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='red')
        axes[0,0].set_title('Rohdaten')
        axes[0,0].set_ylabel('Strom in A')
        axes[0,0].grid(True)
        #erste Mittelwertbildung
        axes[0,1].plot(range(len(Messung.Strom.mittelwerte[0])),Messung.Strom.mittelwerte[0], linestyle = linestyle,marker = '.', markersize= 3, color='red')
        axes[0,1].set_title('Mittelwertbildung $ \overline{x}$, '+'{}'.format(Messung.n))
        axes[0,1].grid(True)

        if (ncols > 2):
            #zweite Mittelwertbildung
            axes[0,2].plot(range(len(Messung.Strom.mittelwerte[1])),Messung.Strom.mittelwerte[1], linestyle =linestyle  ,marker = '.', markersize= 3, color='red')
            axes[0,2].set_title('Mittelwertbildung µ, {}'.format(Messung.k))
            axes[0,2].grid(True)


        #Histogramm Plot

        #rohdaten
        axes[1,0].hist(Messung.Strom.rohdaten, bins=Bins_Strom[0], color='skyblue', edgecolor='black')
        axes[1,0].set_ylabel('Anzahl')
        axes[1,0].grid(True)
        #erste Mittelwertbildung
        axes[1,1].hist(Messung.Strom.mittelwerte[0], bins=Bins_Strom[1], color='skyblue', edgecolor='black')
        axes[1,1].grid(True)

        if (ncols > 2):
        #erste Mittelwertbildung
            axes[1,2].hist(Messung.Strom.mittelwerte[1], bins=Bins_Strom[2], color='skyblue', edgecolor='black')
            axes[1,2].grid(True)


        #QQ-Plot
        sm.qqplot(np.array(Messung.Strom.rohdaten),fit = True, line ='s',ax=axes[2,0])
        # sm.qqplot(np.array(Messung.Strom.rohdaten),scale = Messung.Strom.stat_Auswertung.std,loc = Messung.Strom.stat_Auswertung.mean,line ='s',ax=axes[2,0])
        axes[2,0].grid(True)
        axes[2,0].tick_params(labelbottom=False, labelleft=False)

        sm.qqplot(np.array(Messung.Strom.mittelwerte[0]),fit = True,line ='s',ax=axes[2,1])
        axes[2,1].tick_params(labelbottom=False, labelleft=False)
        axes[2,1].grid(True)

        if (ncols > 2):
            sm.qqplot(np.array(Messung.Strom.mittelwerte[1]),fit = True,line ='s',ax=axes[2,2])
            axes[2,2].tick_params(labelbottom=False, labelleft=False)
            axes[2,2].grid(True)

        # Save Plot
        path = "/media/paul/LINUX_MEM/Fraunhofer/GIT Repos/Master Thesis/Python_Skripte/nna-fpga-power-measurement-system/Python Skript/Normalverteilungstest/"
        plt.savefig(path+figname+'_strom.png', dpi=600)  # Speichert den Plot als 'mein_plot.png' mit 300 dpi Auflösung

# *** Plot Spannung***

    if (1):
        plt.rcParams.update({'font.size': 20})

        # Daten für die Plots generieren

        k = 5
        fig, axes = plt.subplots(nrows,ncols,figsize=(k * 7, k * 10/4))
        fig.canvas.manager.set_window_title(Messung.name)


        #Messdaten Plot
        #rohdaten
        axes[0,0].plot(range(len(Messung.Spannung.rohdaten)),Messung.Spannung.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='blue')
        axes[0,0].set_title('Rohdaten')
        axes[0,0].set_ylabel('Spannung in A')
        axes[0,0].grid(True)
        
        #erste Mittelwertbildung
        axes[0,1].plot(range(len(Messung.Spannung.mittelwerte[0])),Messung.Spannung.mittelwerte[0], linestyle = linestyle, marker = '.', markersize= 3, color='blue')
        axes[0,1].set_title('Mittelwertbildung $ \overline{x}$, '+'{}'.format(Messung.n))
        axes[0,1].grid(True)

        
        #erste Mittelwertbildung
        if (ncols > 2):
            axes[0,2].plot(range(len(Messung.Spannung.mittelwerte[1])),Messung.Spannung.mittelwerte[1], linestyle = linestyle, marker = '.', markersize= 3, color='blue')
            axes[0,2].set_title('Mittelwertbildung µ, {}'.format(Messung.k))
            axes[0,2].grid(True)


        #Histogramm Plot

        #rohdaten
        axes[1,0].hist(Messung.Spannung.rohdaten, bins=Bins_Spannung[0], color='skyblue', edgecolor='black')
        axes[1,0].set_ylabel('Anzahl')
        axes[1,0].grid(True)
        #erste Mittelwertbildung
        axes[1,1].hist(Messung.Spannung.mittelwerte[0], bins=Bins_Spannung[1], color='skyblue', edgecolor='black')
        axes[1,1].grid(True)

        if (ncols > 2):
            #erste Mittelwertbildung
            axes[1,2].hist(Messung.Spannung.mittelwerte[1], bins=Bins_Spannung[2], color='skyblue', edgecolor='black')
            axes[1,2].grid(True)


        #QQ-Plot
        sm.qqplot(np.array(Messung.Spannung.rohdaten),fit = True, line ='s',ax=axes[2,0])
        # sm.qqplot(np.array(Messung.Spannung.rohdaten),scale = Messung.Spannung.stat_Auswertung.std,loc = Messung.Spannung.stat_Auswertung.mean,line ='s',ax=axes[2,0])
        axes[2,0].grid(True)
        axes[2,0].tick_params(labelbottom=False, labelleft=False)

        sm.qqplot(np.array(Messung.Spannung.mittelwerte[0]),fit = True,line ='s',ax=axes[2,1])
        axes[2,1].tick_params(labelbottom=False, labelleft=False)
        axes[2,1].grid(True)


        if (ncols > 2):
            sm.qqplot(np.array(Messung.Spannung.mittelwerte[1]),fit = True,line ='s',ax=axes[2,2])
            axes[2,2].tick_params(labelbottom=False, labelleft=False)
            axes[2,2].grid(True)




        path = "/media/paul/LINUX_MEM/Fraunhofer/GIT Repos/Master Thesis/Python_Skripte/nna-fpga-power-measurement-system/Python Skript/Normalverteilungstest/"
        # plt.savefig(path+figname+'.svg', format='svg')  # Speichert den Plot
        plt.savefig(path+figname+'_spannung'+'.png', dpi=600)  # Speichert den Plot als 'mein_plot.png' mit 300 dpi Auflösung





def rohdaten_darstellen(Messung,figname,line = False):

    #Anzahl Reihen und Zeilen im PLot
    
    nrows = 2
    ncols = 1

    
    #Plot größe skalieren
    k = 5

    #Plot Strom
    plt.rcParams.update({'font.size': 20})

    
    fig, axes = plt.subplots(nrows,ncols,figsize=(k * 7, k * 10/4))
    fig.canvas.manager.set_window_title(Messung.name)

    linestyle = 'None'
    if line:
        linestyle = 'solid'        

    #Messdaten Plot
    #rohdaten Strom
    if (1):
        # X-Achse mit index
        axes[0].plot(range(len(Messung.Strom.rohdaten)),Messung.Strom.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='red')
    else:
        # X-Achse mit Zeitstempel
        axes[0].plot(Messung.Zeit,Messung.Strom.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='red')
    axes[0].set_ylabel('Strom in A')
    axes[0].grid(True)
    

    #rohdaten Spannung
    axes[1].plot(range(len(Messung.Spannung.rohdaten)),Messung.Spannung.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='blue')
    # axes[1].set_title('Rohdaten')
    axes[1].set_ylabel('Spannung in V')
    axes[1].grid(True)
    

    


    path = "/media/paul/LINUX_MEM/Fraunhofer/GIT Repos/Master Thesis/Python_Skripte/nna-fpga-power-measurement-system/Python Skript/Rohdaten/"
    # plt.savefig(path+figname+'.svg', format='svg')  # Speichert den Plot
    plt.savefig(path+figname+'_rohdaten'+'.png', dpi=600)  # Speichert den Plot als 'mein_plot.png' mit 300 dpi Auflösung






   
def komplette_Auswertung_Spannung_Strom(Messung,figname,line = False):
    """
    Erstellt einen Plot, bestehend aus Messdatenplot, Histogramm und QQ-Plot
    mit dem visuel betsimmmt werden kann ob die Messung Normalverteilt ist


    """

    #Berechnungen für das Histogramm
    #Anzahl an Binsund häufigkeit  berechnen für das Histogramm
    Strom = Messung.Strom.rohdaten.copy()    
    Spannung = Messung.Spannung.rohdaten.copy()    

    #Häufigkeit der einzelnen Werte
    Strom.sort()
    Spannung.sort()
    Strom_Bins, Strom_Haeufigkeit = help.calculate_frequencies(Strom)
    Spannung_Bins, Spannung_Haeufigkeit = help.calculate_frequencies(Spannung)

    #lösche bins mit zu wenigen Einträgen, Erster und Letzter
    # del Strom_Bins[0]
    # del Spannung_Bins[0]
    # del Strom_Bins[-1]
    # del Spannung_Bins[-1]<
    # del Strom_Haeufigkeit[0]
    # del Spannung_Haeufigkeit[0]
    # del Strom_Haeufigkeit[-1]
    # del Spannung_Haeufigkeit[-1]
    #Weite der einzelnen Bins
    Weite_Strom = 0.25e-3
    Weite_Spannung = 1.25e-3

    #Berechnung für QQ-Plot
    #quantile der Messung Strom
    # quantile_numbers = np.linspace(1,100,1000)
    quantile_numbers = range(1,100,1)
    sample_quantiles_strom = np.percentile(Messung.Strom.rohdaten,quantile_numbers)

    µ_strom = Messung.Strom.stat_Auswertung.mean
    s_strom = Messung.Strom.stat_Auswertung.std   
    theoretische_normalverteilung_strom = np.random.default_rng().normal(µ_strom, s_strom, len(Messung.Strom.rohdaten))
    theoretrische_quantile_strom= np.percentile(theoretische_normalverteilung_strom, quantile_numbers)
    


    #QQ-plot über Mittelwerte der Spannung, da die Quantisierungsstufen zuu present sind
    if (1):
        µ_spannung = Messung.Spannung.stat_Auswertung_mittelwerte[0].mean
        s_spannung = Messung.Spannung.stat_Auswertung_mittelwerte[0].std
        sample_quantiles_spannung = np.percentile(Messung.Spannung.mittelwerte[0],quantile_numbers)
        theoretische_normalverteilung_spannung= np.random.default_rng().normal(µ_spannung,s_spannung, len(Messung.Spannung.mittelwerte[0]))

    
    else:
    #QQ-Plot über Rohdaten der Spannung
        µ_spannung = Messung.Spannung.stat_Auswertung.mean
        s_spannung = Messung.Spannung.stat_Auswertung.std
        sample_quantiles_spannung = np.percentile(Messung.Spannung.rohdaten,quantile_numbers)
        theoretische_normalverteilung_spannung= np.random.default_rng().normal(µ_spannung,s_spannung, len(Messung.Spannung.rohdaten))
    
    theoretrische_quantile_spannung= np.percentile(theoretische_normalverteilung_spannung, quantile_numbers)

                                                                                                          
                                                                                                          
    # theoretische_normalverteilung_spannung= np.random.default_rng().normal(µ_spannung, s_spannung, len(Messung.Spannung.rohdaten))


    # quantile der Normalverteilung
 

    #checke 
    # Plot
    if (1):
        #Anzahl Reihen und Zeilen im PLot
        nrows = 3
        ncols = 2
        
        #PLot größe skalieren
        k = 5

        plt.rcParams.update({'font.size': 20})
        fig, axes = plt.subplots(nrows,ncols,figsize=(k * 7, k * 10/4))
        fig.canvas.manager.set_window_title(Messung.name)
        # fig.suptitle(Messung.name, fontsize=20)

        #Messpunkte verbinden?
        linestyle = 'None'
        if line:
            linestyle = 'solid'        

    #Messdaten Plot
      
        print(Messung.Strom.stat_Auswertung.mean)
        #rohdaten
    #Strom
        axes[0,0].plot(range(len(Messung.Strom.rohdaten)),Messung.Strom.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='red')
        # axes[0,0].set_title('Messdaten')
        axes[0,0].set_ylabel('Strom in A')
        axes[0,0].grid(True)
        
        #Histogramm
        axes[1,0].bar(Strom_Bins,Strom_Haeufigkeit, width = Weite_Strom, color = 'red',edgecolor='black')
        axes[1,0].set_ylabel('Relative Häufigkeit')
        axes[1,0].grid(True)
        axes[1,0].xaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        # x = np.linspace(µ_strom - 3*s_strom, µ_strom + 3*s_strom, len(theoretrische_quantile_strom))
        # axes[1,0].plot(x, st.norm.pdf(theoretrische_quantile_strom, µ_strom, s_strom)/len(theoretische_normalverteilung_strom))
        # axes[1,0].xaxis.set_tick_params(rotation=45)

        
        #QQ-Plot
        axes[2,0].plot(theoretrische_quantile_strom,sample_quantiles_strom, linestyle = 'none', marker = 'o',color = 'red')
        axes[2,0].plot([min(theoretrische_quantile_strom),max(theoretrische_quantile_strom)],[min(theoretrische_quantile_strom),max(theoretrische_quantile_strom)],color = 'black')
        axes[2,0].grid(True)
        axes[2,0].xaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        axes[2,0].set_ylabel('Reale Quantile')
        axes[2,0].set_xlabel('Theoretische Quantile')
        
        # sm.qqplot(np.array(Messung.Strom.mittelwerte[0]),fit = True, line ='45',ax=axes[2,0])
        # sm.qqplot(np.array(Messung.Strom.mittelwerte[0]),scale = Messung.Strom.stat_Auswertung.std,loc = Messung.Strom.stat_Auswertung.mean, line ='r',ax=axes[2,0])
       
        # axes[2,0].tick_params(labelbottom=False, labelleft=False)

    #Spannung 
        axes[0,1].plot(range(len(Messung.Spannung.rohdaten)),Messung.Spannung.rohdaten, linestyle = linestyle, marker = '.', markersize= 3, color='blue')
        # axes[0,1].set_title('Messdaten')
        axes[0,1].set_ylabel('Spannung in V')
        axes[0,1].grid(True)
        axes[0,1].yaxis.set_label_position('right')
        axes[0,1].yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        axes[0,1].yaxis.set_tick_params(right = True,labelright = True,labelleft = False)

        #Histogramm
        axes[1,1].bar(Spannung_Bins,Spannung_Haeufigkeit, width = Weite_Spannung, color = 'blue',edgecolor='black')
        axes[1,1].set_ylabel('Rlative Häufigkeit')
        axes[1,1].grid(True)
        axes[1,1].yaxis.set_label_position('right')
        axes[1,1].yaxis.set_tick_params(right = True,labelright = True,labelleft = False)
        axes[1,1].xaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        # axes[1,0].xaxis.set_tick_params(rotation=45)

        #QQ-Plot
        # sm.qqplot(np.array(Messung.Spannung.mittelwerte[0]),fit = True, line ='45',ax=axes[2,1])
        axes[2,1].plot(theoretrische_quantile_spannung,sample_quantiles_spannung, linestyle = 'none', marker = 'o', color = 'blue')
        axes[2,1].plot([min(theoretrische_quantile_spannung),max(theoretrische_quantile_spannung)],[min(theoretrische_quantile_spannung),max(theoretrische_quantile_spannung)],color = 'black')
        axes[2,1].grid(True)
        # axes[2,1].tick_params(labelbottom=False, labelleft=False)
        axes[2,1].yaxis.set_label_position('right')
        axes[2,1].yaxis.set_tick_params(right = True,labelright = True,labelleft = False)
        axes[2,1].xaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        axes[2,1].yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
        axes[2,1].set_ylabel('Reale Quantile')
        axes[2,1].set_xlabel('Theoretische Quantile')
        
            #abstände zwischen den Plots
        plt.subplots_adjust(wspace=0)
        fig.subplots_adjust(bottom=0.2)
        # # Save Plot
        # path = "/media/paul/LINUX_MEM/Fraunhofer/GIT Repos/Master Thesis/Python_Skripte/nna-fpga-power-measurement-system/Python Skript/Normalverteilungstest/"
        # plt.savefig(path+figname+'_strom.png', dpi=600)  # Speichert den Plot als 'mein_plot.png' mit 300 dpi Auflösung

def Formelcheck(Messung):
    #Standartverteilungscheck
    if (1):
     
        #standardabweichung nach
        N = len(Messung.Strom.rohdaten)
        mu = Messung.Strom.stat_Auswertung.mean
        mu = sum(Messung.Strom.rohdaten)/N 
        print(mu)
        std = 0
        for data in Messung.Strom.rohdaten:
            std +=  (data-mu)**2
            # print(std)
        standard_verteilung_Formel = np.sqrt(1/(N*(N-1))*std)
        print("Formel:",standard_verteilung_Formel)

        #standardverteilung nach scipy
        print("Scipy trimmed std:",Messung.Strom.stat_Auswertung.std)
        print("Scipy trimmed std mit 1/sqrt(N):",(Messung.Strom.stat_Auswertung.std*1/np.sqrt(N)))
        print("np std:",np.std(Messung.Strom.rohdaten)*1/np.sqrt(N))
        print("Messdatenclass:", Messung.Strom.stat_Auswertung.sigma)
    
def Standartabweichung_Konfidenzintervall(Messung):
    #unbekannte systematische Abweichung
    gain_fehler = 1/np.sqrt(3)*0.02
    print("Gain Fehler:", gain_fehler)
    u_strom = np.sqrt(Messung.Strom.stat_Auswertung.sigma**2+gain_fehler**2)
    u_spannung= np.sqrt(Messung.Spannung.stat_Auswertung.sigma**2+gain_fehler**2)
    print(Messung.name,"Unsicherheit Strom:",u_strom )
    print(Messung.name,"Unsicherheit Spannung:",u_spannung )
    

    # u_3_strom = (3*u_strom/Messung.Strom.stat_Auswertung.mean) *100
    # u_3_spannung= (3*u_spannung/Messung.Spannung.stat_Auswertung.mean) *100




    # #Strom
    # print("Strom:")
    # #Berechnung des 3sigma Konfedenzintervals
    print(Messung.name,", Sigma:", Messung.Strom.stat_Auswertung.sigma*1e3,"mA")
    # print(Messung.name,", 3 Sigma Konfidenzintervall:", 3*Messung.Strom.stat_Auswertung.sigma*1e3,"mA")
    # print(Messung.Strom.stat_Auswertung.mean)
    print(Messung.name,", Sigma: in %", (Messung.Strom.stat_Auswertung.sigma)/Messung.Strom.stat_Auswertung.mean* 100)
    # # print(Messung.name,", 3 Sigma Konfidenzintervall in %:", (3*Messung.Strom.stat_Auswertung.sigma)/Messung.Strom.stat_Auswertung.mean *100)
    # print("Unsicherheit:",u_strom )
    # print(Messung.name,", 3 Sigma Konfidenzintervall in %:", u_3_strom)

    # print("Spannung:")
    # #Berechnung des 3sigma Konfedenzintervals
    print(Messung.name,", Sigma:", Messung.Spannung.stat_Auswertung.sigma*1e3,"mV")
    # # print(Messung.name,", 3 Sigma Konfidenzintervall:", 3*Messung.Spannung.stat_Auswertung.sigma*1e3,"mV")
    # # print(Messung.Spannung.stat_Auswertung.mean)
    # # print(Messung.name,", Sigma: in %", (Messung.Spannung.stat_Auswertung.sigma)/Messung.Spannung.stat_Auswertung.mean* 100)
    # # print(Messung.name,", 3 Sigma Konfidenzintervall in %:", (3*Messung.Spannung.stat_Auswertung.sigma)/Messung.Spannung.stat_Auswertung.mean *100)
    # print(Messung.name,", 3 Sigma Konfidenzintervall in %:", u_3_spannung)

 

def plot_normal_distribution(mean, std_dev, x1, x2,Messung):
    # Erzeugen der X-Werte im gewünschten Bereich
    x = np.linspace(x1, x2, 1000)
    
    # Berechnen der Y-Werte (Wahrscheinlichkeitsdichte) für die Normalverteilung
    y = st.norm.pdf(x, mean, std_dev)
    r = st.norm.rvs(size=len(Messung.Strom.rohdaten))
    plt.plot(r)
    # sm.qqplot(np.array(Messung.Strom.mittelwerte[0]), line ='s')
 
    # Plot der Normalverteilung
    plt.plot(x, y, label=f'Normalverteilung (μ={mean}, σ={std_dev})')
    plt.xlabel('x')
    plt.ylabel('Wahrscheinlichkeitsdichte')
    plt.title('Normalverteilung')
    plt.legend()
    plt.grid(True)
    plt.show()




def qq_Plot(Messung):
    
    #quantile der Messung
    quantile_numbers = range(1,100,1)
    # sample_quantiles = np.percentile(Messung.Strom.mittelwerte[0],quantile_numbers)
    sample_quantiles = np.percentile(Messung.Strom.rohdaten,quantile_numbers)

    print(sample_quantiles)

    # quantile der Normalverteilung
    µ = Messung.Strom.stat_Auswertung.mean
    s = Messung.Strom.stat_Auswertung.std 
    x1 = min(Messung.Strom.rohdaten)
    x2 = max(Messung.Strom.rohdaten)
    # theoretische_normalverteilung = np.random.default_rng().normal(µ, s/np.sqrt(Messung.n), 6000)
    theoretische_normalverteilung = np.random.default_rng().normal(µ, s, 60000)

    # plt.plot(normalverteilung)

    # Berechne Quantile innerhalb der Grenzen x1 und x2

    theoretrische_quantile = np.percentile(theoretische_normalverteilung, quantile_numbers)
    print(theoretrische_quantile)
    plt.plot(theoretrische_quantile,sample_quantiles, linestyle = 'none',marker = 'o')
    plt.plot([min(theoretrische_quantile),max(theoretrische_quantile)],[min(theoretrische_quantile),max(theoretrische_quantile)],color = 'red')
    plt.grid(True)
    # x = st.norm()
    # sm.qqplot(np.array(Messung.Strom.mittelwerte[0]),dist=st.norm,scale = Messung.Strom.stat_Auswertung.std,loc = Messung.Strom.stat_Auswertung.mean, line ='s')
   
    # Beispielaufruf
    # plot_normal_distribution(mean= Messung.Strom.stat_Auswertung.mean, std_dev=Messung.Strom.stat_Auswertung.std, x1=min(Messung.Strom.mittelwerte[0]), x2=max(Messung.Strom.mittelwerte[0]),Messung=Messung)