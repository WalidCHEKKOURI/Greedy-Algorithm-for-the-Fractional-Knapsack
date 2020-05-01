#include <string>
#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

class Object
{
	friend ostream& operator << (ostream& out, const  Object& c);
private:
	int profit;
	int weight;

	string name;

public:
	//constructor
	Object(int profit, string name, int weight)
		:profit{ 0 }, name{ "Unnamed" }, weight{ 0 }
	{
		this-> profit = profit;
		this->name = name;
		this->weight = weight;
	}
	Object()
	{
		profit =0;
		name = "Unnamed" ;
		weight = 0;
	}



	int getProfit()const
	{
		return profit;
	}
	string getName()const
	{
		return name;
	}

	int getWeight()const
	{
		return weight;
	}

	// overloaded > operator
	bool operator >(const Object& o)
	{
		if ((profit/weight) > (o.profit/ o.weight) )
			return true;

		return false;
	}
	// overloaded < operator
	bool operator <(const Object& o)
	{
		if ((profit / weight) < (o.profit / o.weight))
			return true;

		return false;
	}
	
	// overloaded >= operator
	bool operator >=(const Object& o)
	{
		if ((profit / weight) >= (o.profit / o.weight))

			return true;

		return false;
	}

};

//Overload << operator
ostream& operator << (ostream& out, const Object& o)
{
	out << "( " << o.name << " with profit= " << o.profit << " and weight= "<<o.weight<<" )"<<endl;
	return out;
}


// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(Object arr[], int l, int m, int r)//Descending Order
{
	int n = r - l + 1;
	Object* b = new Object[n];
	int left = l, right = m + 1, bIdx = 0;
	while (left <= m && right <= r)
	{
		if (arr[left] >= arr[right])
			b[bIdx++] = arr[left++];
		else
			b[bIdx++] = arr[right++];
	}

	//Remaining items are copied to b[].
	while (left <= m)
		b[bIdx++] = arr[left++];
	while (right <= r)
		b[bIdx++] = arr[right++];

	for (int k = 0; k < n; k++)
		arr[l + k] = b[k];

	delete[] b;//free allocated memory.

}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(Object arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;


		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);

	}
}


void displayObjectsFromArray(Object objects[], const size_t N)
{
	
	for (unsigned int i = 0; i < N; i++)
		cout << objects[i];		

}

void displayObjectsFromKnapsack(vector< pair<Object,  double> > myKnapsack)
{

	for (auto object : myKnapsack)
		cout << object.first.getName() << " with a fraction of: "<< object.second<<endl;
		

}

void solveFractionalKnapsack(Object objects[], const size_t N ,const size_t MAX_CAPACITY )//Greedy Method
{

	mergeSort(objects, 0, N - 1);//Sort objects in descending order based on the Profit/Weight Ratio

	vector< pair<Object, double> > myKnapsack;
	

	double currentCapacity = MAX_CAPACITY;
	double totalWeight = 0;
	double totalProfit = 0;

	unsigned int i = 0;
	for (; i < N; i++)
	{
		if (objects[i].getWeight() <= currentCapacity)
		{
			myKnapsack.emplace_back(objects[i], 1);//add object to our knapsack
			
			//Updating knapsack status
			currentCapacity -= objects[i].getWeight();
			totalWeight += objects[i].getWeight();
			totalProfit += objects[i].getProfit();
			
		}
		else
			break;
			

	}


	if (currentCapacity != 0)//we can still take the last a fraction of the last object
	{
		double fraction = currentCapacity / objects[i].getWeight();
		cout << "here "<<objects[i].getName() << endl;
		//Updating knapsack status
		totalWeight += (fraction * objects[i].getWeight());
		totalProfit += (fraction * objects[i].getProfit());

		myKnapsack.emplace_back(objects[i], fraction);//add object to our knapsack

		cout << "Objects included are: " << endl;
		displayObjectsFromKnapsack(myKnapsack);
		cout << "With total Weight= " << totalWeight << " and total Profit= " << totalProfit << endl;
		return;
	}

	
}


int main()
{

	Object obj1{ 10,"obj1",2 }; Object obj2{ 5,"obj2",3 }; Object obj3{ 15,"obj3",5};
	Object obj4{ 7,"obj4",7 }; Object obj5{ 6,"obj5",1 }; Object obj6{ 18,"obj6",4 };
	Object obj7{ 3,"obj7",1};

	Object objects[] = {obj1, obj2,obj3, obj4,obj5, obj6,obj7};
	const size_t N = sizeof(objects) / sizeof(objects[0]);

	const size_t MAX_CAPACITY = 15;

	solveFractionalKnapsack(objects, N, MAX_CAPACITY);
	
	


	system("pause");
	return 0;
}