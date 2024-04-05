import csv 
def csv_to_lists(csv_file):
    # Listen für Zeit, Spannung, Strom und Leistung erstellen
    zeit = []
    spannung = []
    strom = []
    leistung = []

    try:
        with open(csv_file, 'r') as file:
            csv_reader = csv.reader(file)
            next(csv_reader)  # Überspringe die Header-Zeile, falls vorhanden

            for row in csv_reader:
                # Annahme: Die CSV-Datei hat die Spaltenreihenfolge Zeit, Spannung, Strom, Leistung
                zeit.append(float(row[0]))
                spannung.append(float(row[1]))
                strom.append(float(row[2]))
                leistung.append(float(row[3]))

    except FileNotFoundError:
        print(f'Die Datei "{csv_file}" wurde nicht gefunden.')

    return zeit, spannung, strom, leistung


def zeitstempel_statistik(zeitstempel_liste):
    # Sortiere die Liste der Zeitstempel
    zeitstempel_liste.sort()
    
    # Berechne die Differenzen zwischen benachbarten Zeitstempeln
    differenzen = [zeitstempel_liste[i+1] - zeitstempel_liste[i] for i in range(len(zeitstempel_liste)-1)]
    
    # Berechne den größten, den kleinsten und den durchschnittlichen Abstand
    groesster_abstand = max(differenzen)
    kleinster_abstand = min(differenzen)
    durchschnittlicher_abstand = sum(differenzen) / len(differenzen)
    
    return groesster_abstand, kleinster_abstand, durchschnittlicher_abstand




def calculate_frequencies(data):
    unique_values = []
    frequencies = []
    for value in data:
        if value not in unique_values:
            unique_values.append(value)
            frequencies.append(1)
        else:
            index = unique_values.index(value)
            frequencies[index] += 1
#Werte normalisieren
    for i in range(len(frequencies)):
        frequencies[i] = frequencies[i]/len(data)
    return unique_values, frequencies