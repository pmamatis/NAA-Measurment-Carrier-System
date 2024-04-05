import helper as help
import numpy as np
from scipy import stats as st
import matplotlib.pyplot as plt

class Daten_t:
    def __init__(self, rohdaten, n, LSB):
        self.LSB = LSB
        # self.rohdaten = rohdaten
        #Korrektur des Stroms
        offset = 0.75e-3
        shunt_offset = 3.5e-3
        self.rohdaten = [rohdaten[i]-(offset+shunt_offset)for i in range(len(rohdaten))]
        self.mittelwerte = [[],[]] #menge von Mittelwerten
        self.get_mittelwerte(n)
        self.stat_Auswertung = statistischeAuswertung_t(self.rohdaten) 
        self.stat_Auswertung_mittelwerte = []
        self.stat_Auswertung_mittelwerte.append(statistischeAuswertung_t(self.mittelwerte[0])) 
        # self.stat_Auswertung_mittelwerte.append(statistischeAuswertung_t(self.mittelwerte[1]))


    def get_mittelwerte(self, N):

        #Korrektur des Stroms
        # offset = 0.75e-3
        # shunt_offset = 3.5e-3
        # self.rohdaten = [self.rohdaten[i]-(offset+shunt_offset)for i in range(len(self.rohdaten))]
        liste = self.rohdaten
        #mittelwerte berechnen sodass N mittelwerte 1ms ergeben
        for i in range(0, len(liste), N):
            teil_liste = liste[i:i+N]
            if len(teil_liste) == N:
                self.mittelwerte[0].append(np.mean(teil_liste))
        # erneute Mittelwertbildung für statistische Auswertung über K Werte
        K = 100
        for i in range(0, len(self.mittelwerte[0]), K):
            teil_liste = liste[i:i+K]
            if len(teil_liste) == K:
                self.mittelwerte[1].append(np.mean(teil_liste))

class Auswertung_t:
    def __init__(self, name, messzeit, dateipfad, n, k=100, index1 = 0, index2 = 0):
        self.name = name
        self.messzeit = messzeit #in µs
        self.dateipfad = dateipfad
        self.n = n #Anzahl der Werte um 1ms zu erreichen
        self.k = k #Anzahl der Werte einer Messreihe für statistische Auswertung, default = 100
        rohdaten = help.csv_to_lists(self.dateipfad)
        if index2 == 0:
            index2 = len(rohdaten[0])
        self.Zeit = rohdaten[0][index1:index2]
        self.deltaT = help.zeitstempel_statistik(self.Zeit)
        self.Spannung = Daten_t(rohdaten[1][index1:index2],n, 1.25e-3)
        self.Strom = Daten_t(rohdaten[2][index1:index2],n,0.25e-3)
        self.Leistung = rohdaten[3][index1:index2]
        self.std_Strom  = st.stats.tstd

class statistischeAuswertung_t:
    def __init__(self, datensatz):
        self.std = st.tstd(datensatz) #standardabweichung
        self.mean = sum(datensatz)/len(datensatz) #Mittelwert
        print(self.mean)
        self.sigma = self.std*1/np.sqrt(len(datensatz)) #standardabweichung mit Faktor 1/n^1/2
        

       
        


