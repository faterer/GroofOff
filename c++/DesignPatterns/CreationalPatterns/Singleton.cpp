// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Singleton
// The Singleton pattern ensures that a class has only one instance and provides a global point
//  of access to that instance. It is named after the singleton set, which is defined to be a 
//  set containing one element. This is useful when exactly one object is needed to coordinate 
//  actions across the system.
// Check list
// Define a private static attribute in the "single instance" class.
// Define a public static accessor function in the class.
// Do "lazy initialization" (creation on first use) in the accessor function.
// Define all constructors to be protected or private.
// Clients may only use the accessor function to manipulate the Singleton.
// Let's take a look at how a Singleton differs from other variable types.
// Like a global variable, the Singleton exists outside of the scope of any functions. 
// Traditional implementation uses a static member function of the Singleton class, 
// which will create a single instance of the Singleton class on the first call, and 
// forever return that instance. The following code example illustrates the elements 
// of a C++ singleton class, that simply stores a single string. 
class StringSingleton
{
public:
	// Some accessor functions for the class, itself
	std::string GetString() const
	{ return mString; }

	// The magic function, which allows access to the class from anywhere
	// To get the value of the instance of the class, call:
	// StringSingleton::Instance().GetString();
	static StringSingleton &Instance()
	{
		// This line only runs once, thus creating the only instance in existance
		static StringSingleton *instance = new StringSingleton;
		// dereferencing the variable here, saves the caller from having to use 
		// the arrow operator, and removes temptation to try and delete the 
		// returned instance.		
		return *instance;
	}

private: 
	// private data for an instance of this class
	std::string mString;
	// We need to make some given functions private to finish the definition of the singleton
	StringSingleton(){} // default constructor available only to members or friends of this class
	// Note that although this should be allowed, 
	// some compilers may not implement private destructors
	// This prevents others from deleting our one single instance, which was otherwise created 
	// on the heap
	~StringSingleton(){}
	// Note that the next two functions are not given bodies, thus any attempt 
	// to call them implicitly will return as compiler errors. This prevents 
	// accidental copying of the only instance of the class.
     StringSingleton(const StringSingleton &old); // disallow copy constructor
     const StringSingleton &operator=(const StringSingleton &old); //disallow assignment operator	
};

// API Design for C++
// Simple Singleton example, not thread safe
// Singleton& obj = Singleton::GetInstance();
class Singleton
{
public:
	static Singleton &GetInstance() {
		static Singleton instance;
		return instance;
	}
private:
	Singleton();
	~Singleton();
	Singleton(const Singleton &);
	const Singleton &operator=(const Singleton &);
};


//Variations of Singletons:
// Applications of Singleton Class:
// One common use of the singleton design pattern is for application configurations. 
// Configurations may need to be accessible globally, and future expansions to the 
// application configurations may be needed. The subset C's closest alternative would
// be to create a single global struct. This had the lack of clarity as to where this
// object was instantiated, as well as not guaranteeing the existence of the object.
// Take, for example, the situation of another developer using your singleton inside 
// the constructor of their object. Then, yet another developer decides to create an 
// instance of the second class in the global scope. If you had simply used a global 
// variable, the order of linking would then matter. Since your global will be accessed, 
// possibly before main begins executing, there is no definition as to whether the global 
// is initialized, or the constructor of the second class is called first. This behavior 
// can then change with slight modifications to other areas of code, which would change 
// order of global code execution. Such an error can be very hard to debug. But, with use
// of the singleton, the first time the object is accessed, the object will also be created. 
// You now have an object which will always exist, in relation to being used, and will never 
// exist if never used.
// A second common use of this class is in updating old code to work in a new architecture. 
// Since developers may have used globals liberally, moving them into a single class and making 
// it a singleton, can be an intermediary step to bring the program inline to stronger object 
// oriented structure.
/* Place holder for thread synchronization mutex */
class Mutex
{   /* placeholder for code to create, use, and free a mutex */
};

/* Place holder for thread synchronization lock */
class Lock
{   public:
        Lock(Mutex& m) : mutex(m) { /* placeholder code to acquire the mutex */ }
        ~Lock() { /* placeholder code to release the mutex */ }
    private:
        Mutex & mutex;
};

class Singleton
{   public:
        static Singleton* GetInstance();
        int a;
        ~Singleton() { cout << "In Destructor" << endl; }

    private:
        Singleton(int _a) : a(_a) { cout << "In Constructor" << endl; }
    

        static Mutex mutex;

        // Not defined, to prevent copying
        Singleton(const Singleton& );
        Singleton& operator =(const Singleton& other);
};

Mutex Singleton::mutex;

Singleton* Singleton::GetInstance()
{
    Lock lock(mutex);

    cout << "Get Instance" << endl;

    // Initialized during first access
    static Singleton inst(1);

    return &inst;
}

int main()
{
    Singleton* singleton = Singleton::GetInstance();
    cout << "The value of the singleton: " << singleton->a << endl;
    return 0;
}

//use pthread_once make thread safe singleton from Muduo
//Singleton<T>::instance()
template<typename T>
class Singleton : boost::noncopyable
{
public:
	static T& instance()
	{
		// std::call_once(&callonce_, &Singleton::init); c++11
		pthread_once(&ponce_, &Singleton::init); 
		return *value_;
	}

private:
	Singleton();
	~Singleton();

	static void init()
	{
		value_ = new T();
		::atexit(destroy); // pointer to a function to be called on normal program termination
	}

	static void destroy()
	{
		delete value_;
	}

private:
	static pthread_once_t ponce_; //static std::once_flag callonce_;
	static T*			  value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

class Test : boost::noncopyable
{
public:
	Test() {}
	~Test() {}

	const std::string& name() const { return name_; }
	void setName(const std::string& n) { name_ = n; }
private:
	std::string name_;
};

int main()
{
	Singleton<Test>::instance.setName("only one");
}