// Composite
// Composite lets clients treat individual objects and compositions of objects uniformly. 
// The Composite pattern can represent both the conditions. In this pattern, 
// one can develop tree structures for representing part-whole hierarchies.
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class Graphic
{
public:
	virtual void print() const = 0;
	virtual ~Graphic() {}
};

class Ellipse : public Graphic
{
public:
	void print() const {
		cout << "Ellipse \n";
	}
};

class CompositeGraphic : public Graphic
{
public:
	void print() const {
		for_each(graphicList_.begin(), graphicList_.end(), [](Graphic* a){a->print();});
	}

	void add(Graphic *aGraphic) {
		graphicList_.push_back(aGraphic);
	}

private:
	vector<Graphic*> graphicList_;
};

int main()
{
	// Initialize four ellipes
	const unique_ptr<Ellipse> ellipes1(new Ellipse());
	const unique_ptr<Ellipse> ellipes2(new Ellipse());
	const unique_ptr<Ellipse> ellipes3(new Ellipse());
	const unique_ptr<Ellipse> ellipes4(new Ellipse());

	// Initialize three composite graphics
	const unique_ptr<CompositeGraphic> graphic(new CompositeGraphic());
	const unique_ptr<CompositeGraphic> graphic1(new CompositeGraphic());
	const unique_ptr<CompositeGraphic> graphic2(new CompositeGraphic());

	graphic1->add(ellipes1.get());
	graphic1->add(ellipes2.get());
	graphic1->add(ellipes3.get());

	graphic2->add(ellipes4.get());

	graphic->add(graphic1.get());
	graphic->add(graphic2.get());

	graphic->print();
	return 0;
}