// Prototype
// A prototype pattern is used in software development when the type of objects to create 
// is determined by a prototypical instance, which is cloned to produce new objects. 
// This pattern is used, for example, when the inherent cost of creating a new object in 
// the standard way (e.g., using the new keyword) is prohibitively expensive for a given application.
// Implementation: Declare an abstract base class that specifies a pure virtual clone() method. 
// Any class that needs a "polymorphic constructor" capability derives itself from the abstract 
// base class, and implements the clone() operation.
// Here the client code first invokes the factory method. This factory method, depending on the 
// parameter, finds out the concrete class. On this concrete class, the clone() method is called 
// and the object is returned by the factory method.
// This is a sample implementation of Prototype method. We have the detailed description of all 
// the components here.
// Record class, which is a pure virtual class that has a pure virtual method clone().
// CarRecord, BikeRecord and PersonRecord as concrete implementation of a Record class.
// An enum RecordType as one to one mapping of each concrete implementation of Record class.
// RecordFactory class that has a Factory method CreateRecord(…). This method requires an enum 
// RecordType as parameter and depending on this parameter it returns the concrete implementation 
// of Record class.

// Record is the base Prototype
class Record
{
public:
	virtual ~Record() {}
	virtual void print() = 0;
	virtual unique_ptr<Record> clone() = 0;
};

// CarRecord is a Concrete Prototype
class CarRecord : public Record
{
private:
	string m_carName;
	int m_ID;
public:
	CarRecord(string carName, int ID) 
		: m_carName(carName), m_ID(ID)
	{		
	}

	void print() override
	{
		cout << "Car Record" << endl
		     << "Name  : "   << m_carName << endl
		     << "Number: "   << m_ID << endl << endl;		
	}

	unique_ptr<Record> clone() override
	{
		return make_unique<CarRecord>(*this);
	}
};

// BikeRecord is the Concrete Prototype
class BikeRecord : public Record
{
private:
	string m_bikeName;
	int m_ID;

public:
	BikeRecord(string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID)
	{
	}

	void print() override
	{
		cout << "Bike Record" << endl
		     << "Name  : " << m_bikeName << endl
		     << "Number: " << m_ID << endl << endl;
	}

	unique_ptr<Record> clone() override
	{
		return make_unique<BikeRecord>(*this);
	}
};

// PersonRecord is the Concrete Prototype
class PersonRecord : public Record
{
private:
	string m_personName;
	int m_age;

public:
	PersonRecord(string personName, int age) : m_personName(personName), m_age(age)
	{
	}

	void print() override
	{
		cout << "Person Record" << endl
			<< "Name : " << m_personName << endl
			<< "Age  : " << m_age << endl << endl;
	}

	unique_ptr<Record> clone() override
	{
		return make_unique<PersonRecord>(*this);
	}
};

/** Opaque record type, avoids exposing concrete implementations */
enum RecordType
{
	CAR,
	BIKE,
	PERSON
};

/** RecordFactory is the client */
class RecordFactory
{
private:
	unordered_map<RecordType, unique_ptr<Record>, hash<int> > m_records;

public:
	RecordFactory()
	{
		m_records[CAR]    = make_unique<CarRecord>("Ferrari", 5050);
		m_records[BIKE]   = make_unique<BikeRecord>("Yamaha", 2525);
		m_records[PERSON] = make_unique<PersonRecord>("Tom", 25);
	}

	unique_ptr<Record> createRecord(RecordType recordType)
	{
		return m_records[recordType]->clone();
	}
};

int main()
{
	RecordFactory recordFactory;

	auto record = recordFactory.createRecord(CAR);
	record->print();

	record = recordFactory.createRecord(BIKE);
	record->print();

	record = recordFactory.createRecord(PERSON);
	record->print();
}