// Klaudia C - 29.04.2016

#include <string>
#include <cstring>
using namespace std;

class Warehouse;
class Aisle;
class Section;
class Item;
class Location;
class WarehouseItem;


class Item{
	string name;

    public:
    Item(const string &name) : name(name){}

    string getName() const{
		return name;
	}
};

class Location{
	const Warehouse &warehouse;
	const Aisle &aisle;
	const Section &section;
	int shelf;

    public:
    Location(const Warehouse &_warehouse, const Aisle &_aisle, const Section &_Section, int _shelf)
		: warehouse(_warehouse), aisle(_aisle), section(_Section), shelf(_shelf){}

    const Aisle &getAisle() const{
		return aisle;
    }

    const Section &getSection() const{
		return section;
    }

    const Warehouse &getWarehouse() const{
		return warehouse;
    }

    int getShelf() const{
		return shelf;
    }
};

class WarehouseItem{
	Item item;
	Location location;

    friend class Warehouse;

    public:
    WarehouseItem(const Item &item, const Location &_location)
		:item(item), location(_location.getWarehouse(), _location.getAisle(), _location.getSection(), _location.getShelf()){}

    const Item &getItem() const{
		return item;
    }

    const Location &getLocation() const{
		return location;
    }
};


class Section{
    int number;
    int shelvesNumber;
    int itemsNumber;
    WarehouseItem **items;

    friend class Warehouse;

    public:
    Section(int number, int shelvesNumber): number(number), shelvesNumber(shelvesNumber), itemsNumber(0), items(NULL){}

    Section(const Section &other): number(other.number), shelvesNumber(other.shelvesNumber), itemsNumber(0), items(NULL){}

    ~Section(){
		for(int i = 0; i < itemsNumber; i++) delete items[i];
		delete items;
	}

    int getShelvesNumber() const{
        return shelvesNumber;
    }

    int getNumber() const{
        return number;
    }

    WarehouseItem *const *getItems() const{
        return items;
    }

    int getItemsNumber() const{
        return itemsNumber;
    }
};

class Aisle{
    int number;
    int sectionsNumber;
    Section **sections;

	friend class Warehouse;

    public:
    Aisle(int number, int sectionsNumber, Section **sections): number(number), sectionsNumber(sectionsNumber), sections(sections){}

    Aisle(const Aisle &other): number(other.number), sectionsNumber(other.sectionsNumber){
		sections = new Section*[sectionsNumber];
		for(int i = 0; i < sectionsNumber; i++) sections[i] = new Section(*other.sections[i]);
    }

	~Aisle(){
		for(int i = 0; i < sectionsNumber; i++) delete sections[i];
		delete sections;
	}

    int getNumber() const{
		return number;
    }

    Section *const *getSections() const{
        return sections;
    }

    int getSectionsNumber() const{
        return sectionsNumber;
    }
};

class Warehouse{
	string name;
	int aislesNumber;
	Aisle **aisles;

	public:
    class ItemSequence{
		WarehouseItem ** first, ** last, ** act;
		ItemSequence(){}

		friend class Warehouse;

		public:
		ItemSequence(const ItemSequence &other){
			first = new WarehouseItem* [other.last - other.first];
			last = first + (other.last - other.first);
			act = first + (other.act - other.first);
			for(int i = 0; i < last - first; i++) first[i] = other.first[i];
		}

		~ItemSequence(){
			delete first;
		}

		WarehouseItem *next(){
			if(act == last) return NULL;
			return *(act++);
		}

		void reset(){
			act = first;
		}
	};

    public:
    Warehouse(const string &name, int aislesNumber, Aisle **aisles): name(name), aislesNumber(aislesNumber), aisles(aisles){}

	~Warehouse(){
		for(int i = 0; i < aislesNumber; i++){
			delete aisles[i];
		}
		delete aisles;
	}

    string getName() const{
		return name;
	}

    Aisle *const *getAisles() const{
		return aisles;
	}

    int getAislesNumber() const{
		return aislesNumber;
	}

    WarehouseItem *addItem(const Item &p, int aisleNr, int sectionNr, int shelfNr){
		WarehouseItem *newItem = new WarehouseItem(p, Location(*this, *(getAisles()[aisleNr - 1]), *(getAisles()[aisleNr - 1] -> getSections()[sectionNr - 1]), shelfNr));
		WarehouseItem **oldList = aisles[aisleNr - 1] -> sections[sectionNr - 1] -> items;
		int itemsNumber = aisles[aisleNr - 1] -> sections[sectionNr - 1] -> itemsNumber++;
		WarehouseItem **newList = new WarehouseItem*[itemsNumber + 1];
		aisles[aisleNr - 1] -> sections[sectionNr - 1] -> items = newList;

		for(int i = 0; i < itemsNumber; i++) newList[i] = oldList[i];
		newList[itemsNumber] = newItem;

		delete oldList;
		return newItem;
	}

    void deleteItem(WarehouseItem *wItem){
		int aisleNr = wItem -> location.getAisle().getNumber();
		int sectionNr = wItem -> location.getSection().getNumber();
		WarehouseItem **oldList = aisles[aisleNr - 1] -> sections[sectionNr - 1] -> items;
		int itemsNumber = --aisles[aisleNr - 1] -> sections[sectionNr - 1] -> itemsNumber;
		WarehouseItem**newList = itemsNumber ? new WarehouseItem*[itemsNumber] : NULL; // co jesli pusta??
		int i = 0;

		while(oldList[i] != wItem){
			newList[i] = oldList[i];
			i++;
		}
		while(i < itemsNumber){
			newList[i] = oldList[i + 1];
			i++;
		}

		aisles[aisleNr - 1] -> sections[sectionNr - 1] -> items = newList;

		delete wItem;
		delete oldList;
	}

    ItemSequence search(const string &namePrefix) const{
		ItemSequence res;
		int size = 0;

		for(int i = 0; i < getAislesNumber(); i++){
			Aisle *aisle = getAisles()[i];
			for(int j = 0; j < aisle -> getSectionsNumber(); j++){
				Section *section = aisle -> getSections()[j];
				for (int k = 0; k < section -> getItemsNumber(); k++){
					WarehouseItem *warehouseItem = section -> getItems()[k];
					if(warehouseItem -> getItem().getName().find(namePrefix) == 0) size++;
				}
			}
		}
		res.act = res.first = new WarehouseItem*[size];
		res.last = res.first + size;

		for(int i = 0; i < getAislesNumber(); i++){
			Aisle * aisle = getAisles()[i];
			for(int j = 0; j < aisle -> getSectionsNumber(); j++){
				Section *section = aisle -> getSections()[j];
				for (int k = 0; k < section -> getItemsNumber(); k++){
					WarehouseItem *warehouseItem = section -> getItems()[k];
					if(warehouseItem -> getItem().getName().find(namePrefix) == 0) *(res.act++) = warehouseItem;
				}
			}
		}
		res.act = res.first;
		return res;
	}
};
