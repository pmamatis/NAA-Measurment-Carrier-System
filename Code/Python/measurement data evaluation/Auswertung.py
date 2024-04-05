import Statistische_Auswertung_Funtionen as SA
import Messdaten_class as Mc
import matplotlib.pyplot as plt
import datetime as dt

Auswertung_Normalverteilungstest_timesweep = False
Auswertung_Normalverteilungstest_currentsweep= False
Auswertung_Genauer_600_Messwerte = False
MesszeitenNachweis = False
EinMittelwert_timesweep = False
EinMittelwert_currentsweep = False
Komplette_Auswertung = False
Histogramm = False
Auswertung_fuer_die_Thesis = False
standartverteilungs_Gleichung_Überprüfen = False
Konfidenzintervalle = True
QQ_Plot =  False
# ***Messdaten einlesen***

# Aktuelles Datum und Uhrzeit
now = dt.datetime.now()

# Formatierter Zeitstempel
formatted_timestamp = now.strftime("%Y-%m-%d_%H-%M-%S")

# ***Messzeiten vergleich***
if (Auswertung_Normalverteilungstest_timesweep):
    path = "path/to/measurmentdata/"
    Messung = []
    Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',7))
    Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',5))
    Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',3))
    Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',2))
    print("Daten eingelesen")
    for i in range(len(Messung)):
        SA.Normalverteilungstest(Messung[i], formatted_timestamp + "_normtest_" + Messung[i].name)


  
# ***Messung verschiedener Ströme*** 
if (Auswertung_Normalverteilungstest_currentsweep):  
    path = "path/to/measurmentdata/"
    Messung = []
    # ***korrigierte komplette Messung ***
    index1 = 1000000
    index2 = 2800000
    Messung.append(Mc.Auswertung_t('1A',588,path + 'Streuung.csv',2, index1= index1, index2=index2))
    Messung.append(Mc.Auswertung_t('3A',588,path + 'Streuung3A.csv',2, index1= index1, index2=index2))
    Messung.append(Mc.Auswertung_t('5A',588,path + 'Streuung5A5.csv',2,index1=index1, index2=index2))
    print("Daten eingelesen")
    for i in range(len(Messung)):
        SA.Normalverteilungstest(Messung[i], formatted_timestamp + "_normtest_" + Messung[i].name)




# ***Weniger Messdaten***
if(Auswertung_Genauer_600_Messwerte):
    path = "path/to/measurmentdata/"    Messung = []
    index1 = 1000000
    index2 = 1000600
    Messung.append(Mc.Auswertung_t('1A',588,path + 'Streuung.csv',2, index1= index1, index2=index2))
    Messung.append(Mc.Auswertung_t('3A',588,path + 'Streuung3A.csv',2, index1= index1, index2=index2))
    Messung.append(Mc.Auswertung_t('5A',588,path + 'Streuung5A5.csv',2,index1=index1, index2=index2))
    print("Daten eingelesen")
    for i in range(len(Messung)):
        # SA.Normalverteilungstest(Messung[i], formatted_timestamp + "_normtest_" + Messung[i].name,line=True)
        SA.rohdaten_darstellen(Messung[i], formatted_timestamp + "_less_" + Messung[i].name,line=True)
if (MesszeitenNachweis):
        path = "path/to/measurmentdata/"        Messung = []
        Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',7))
        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',5))
        Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',3))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',2))

        path = "path/to/measurmentdata.csv"
        index1 = 1000000
        index2 = 2800000
        Messung.append(Mc.Auswertung_t('1A',588,path + 'Streuung.csv',2, index1= index1, index2=index2))
        Messung.append(Mc.Auswertung_t('3A',588,path + 'Streuung3A.csv',2, index1= index1, index2=index2))
        Messung.append(Mc.Auswertung_t('5A',588,path + 'Streuung5A5.csv',2,index1=index1, index2=index2))
        # print("Daten eingelesen")
        print("Zeitstempelabstände  größter kleinster   avg")
        for i in range(len(Messung)):
             print(Messung[i].name + ": "+str(Messung[i].deltaT[0])+"   "+str(Messung[i].deltaT[1])+"   "+str(Messung[i].deltaT[2]))

# *** Normalverteilungstest mit 1-Mittelwertbildung der verscheidenen Messzeiten des Sensors***
if (EinMittelwert_timesweep):
        path = "path/to/measurmentdata/"        Messung = []
        Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',100, k=0))
        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',100, k=0))
        Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',100, k=0))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',100, k=0))
        print("Daten eingelesen")
        for i in range(len(Messung)):
            SA.Normalverteilungstest(Messung[i], formatted_timestamp + "_normtest_" + Messung[i].name)




# *** Normalverteilungstest mit 1-Mittelwertbildung der verscheidenen Strömstärken***
if (EinMittelwert_currentsweep):
        Messung = []
        path = "path/to/measurmentdata/"
        index1 = 1000000
        index2 = 2800000
        Messung.append(Mc.Auswertung_t('1A',588,path + 'Streuung.csv',100, k=0, index1= index1, index2=index2))
        Messung.append(Mc.Auswertung_t('3A',588,path + 'Streuung3A.csv',100, k=0, index1= index1, index2=index2))
        Messung.append(Mc.Auswertung_t('5A',588,path + 'Streuung5A5.csv',100, k=0,index1=index1, index2=index2))
        print("Daten eingelesen")
        for i in range(len(Messung)):
            SA.Normalverteilungstest(Messung[i], formatted_timestamp + "_normtest_" + Messung[i].name)


if (Komplette_Auswertung):
        path = "path/to/measurmentdata/"        Messung = []
        Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',100, k=0))
        SA.komplette_Auswertung_Spannung_Strom(Messung[0])
     
if (Histogramm):
        path = "path/to/measurmentdata/"        Messung = []
        Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',100, k=0))
        # Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',100, k=0))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',100, k=0))
        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',100, k=0))
        print("Daten eingelesen")

        for i in range(len(Messung)): 
            SA.Histogramm(Messung[i])
# *** Auswertungsplots für die Thesis***
if (Auswertung_fuer_die_Thesis):
        path = "path/to/measurmentdata/"        Messung = []
        index1 = 10300
        index2 = 10400
        n =  10
        # Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',n = 10, k=0))

        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',n = n, k=0))
        # Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',n = 1, k=0, index1=index1, index2=index2)) 
        # Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',n = 10, k=0))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',n = n, k=0))
        # Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',n = 1, k=0, index1=index1, index2=index2))

        print("Daten eingelesen")
        #Plots der kompletten Messreihen
        for i in range(len(Messung)): 
            SA.komplette_Auswertung_Spannung_Strom(Messung[i],formatted_timestamp + "_thesisAuswertung_" + Messung[i].name)
        
# *** Berechnung der 3sigma-Konfidenzintervalle der Messung***
if (Konfidenzintervalle):
        path = "path/to/measurmentdata/"        Messung = []
        #statistische Auswertung über 100 Werte
        index1 = 20000
        index2 = 20100
        # Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',n = 10, k=0, index1=index1, index2=index2))
        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',n = 10, k=0, index1=index1, index2=index2))
        # Messung.append(Mc.Auswertung_t('332µs',332,path + '332u.csv',n = 10, k=0, index1=index1, index2=index2))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',n = 10, k=0, index1=index1, index2=index2))
        print("Koinfedenzintervalle über", index2-index1,"Werte")
        for i in range(len(Messung)):
            SA.Standartabweichung_Konfidenzintervall(Messung[i])


# *** Vergleich der Ergebnisse der Standardabweichungen verschiedener Librarys***
if (standartverteilungs_Gleichung_Überprüfen):
        path = "path/to/measurmentdata/"        Messung = []
        Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',n = 10, k=0))
        SA.Formelcheck(Messung[0])

# *** Erstellung eines eigenen QQ-Plots um die Achsern Richtig beschriften zu können ***
if (QQ_Plot):
        path = "path/to/measurmentdata/"        Messung = []
        # Messung.append(Mc.Auswertung_t('140µs',140,path + '140u.csv',n = 10, k=0))  

        Messung.append(Mc.Auswertung_t('204µs',204,path + '204u.csv',n = 10, k=0))
        Messung.append(Mc.Auswertung_t('588µs',588,path + '588u.csv',n = 10, k=0))
        SA.qq_Plot(Messung[0])
        SA.qq_Plot(Messung[1])

plt.show()


