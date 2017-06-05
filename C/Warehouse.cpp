#include "Warehouse.h"
#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;

void printLocation(const Location &loc){
    cout << loc.getWarehouse().getName()
         << "-" << loc.getAisle().getNumber()
         << "-" << loc.getSection().getNumber()
         << "-" << loc.getShelf();
}

void printWarehouseItem(const WarehouseItem &item){
    cout << item.getItem().getName() << " ";
    printLocation(item.getLocation());
    cout << endl;
}

void printWarehouse(const Warehouse &war){
    cout << "warehouse " << war.getName() << ":" << endl;
    for(int i = 0; i < war.getAislesNumber(); i++){
        Aisle *aisle = war.getAisles()[i];
        cout << "aisle " << aisle -> getNumber() << ":" << endl;
        for(int j  = 0; j < aisle -> getSectionsNumber(); j++){
            Section *section = aisle -> getSections()[j];
            cout << " section " << section -> getNumber() << ":" << endl;
            for(int k = 0; k < section -> getItemsNumber(); k++){
                cout << "        ";
                printWarehouseItem(*section -> getItems()[k]);
            }
        }
    }
}

int main(int argc, char** argv){
//Tworzymy magazyn, o dlugosciach alejek 4 5 i 6
//pierwsze 4 sekcje z alejki maja 4 polki, pozostale 3
    Section ***sections =  new Section**[3];
    Aisle **aisles = new Aisle*[3];
    for(int i = 0; i < 3; i++){
        sections[i] = new Section*[i+4];
        for(int j = 0; j < i + 4; j++){
            sections[i][j] = new Section(j + 1, 3 + ((j < 4) ? 1 : 0));
        }
        aisles[i] = new Aisle(i + 1, i + 4, sections[i]);
    }
    delete [] sections;
    Warehouse war("W1", 3, aisles);

    //Dodajemy przedmioty
    printWarehouseItem(*war.addItem(Item("Tlumik 122 Pal."), 1, 1, 1));
    printWarehouseItem(*war.addItem(Item("Tlumik 151 Pal."), 1, 2, 1));
    printWarehouseItem(*war.addItem(Item("Resor 1218 Pal."), 2, 1, 1));
    printWarehouseItem(*war.addItem(Item("Resor 1219 Pal."), 3, 6, 3));
    printWarehouseItem(*war.addItem(Item("Amortyzator 1329 Skrz."), 1, 3, 2));
    printWarehouseItem(*war.addItem(Item("Amortyzator 1379 Skrz."), 2, 1, 1));

    //Wypisujemy
    printWarehouse(war);

    //Kopia alejek, przedmioty NIE sa kopiowane
    Aisle aisle = (*war.getAisles()[1]);
    Section s(*aisle.getSections()[0]);

    cout << s.getItemsNumber() << endl;

    //Przyklad wyszukiwania i iteracji po sekwencji przedmiotow.
    Warehouse::ItemSequence seq = war.search("Resor");
    cout << "TUTAJ" << endl;
    WarehouseItem * it;
    while((it = seq.next()) != NULL){
        printWarehouseItem(*it);
    }

    seq.reset();

    //Przyklady usuwania
    war.deleteItem(seq.next());
    war.deleteItem(war.getAisles()[0]->getSections()[0]->getItems()[0]);
    cout << endl;
    printWarehouse(war);

    return 0;
}
