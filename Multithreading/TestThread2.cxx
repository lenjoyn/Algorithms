#include"iostream"
#include"future"

int RunFunction(int k){

     int p=0;
     for(int i=0; i<k; i++) p++;
     std::cout<<"running Function\n";
     return p;
     
}

class RunFunctor{
public:
	int operator()(int &k){
		std::cout<<"running Fuctor\n";
		int p=0;
		for(int i=0; i<k; i++) p++;
		return p;
	}

};

auto RunLambda = [&](int k)->int{  
	 std::cout<<"running Lambda\n";
	 int p=0; 
         for(int i=0; i<k; i++) p++;
	 return p;

};


int main(){


	RunFunctor func;
	std::future<int> t1=std::async(RunFunction, 3);
	std::future<int> t3=std::async(RunLambda, 5);
	int p=4;
	std::future<int> t2=std::async(func, std::ref(p));


	std::cout<<"done thread1 "<<t1.get()<<"\n";
	std::cout<<"done thread2 "<<t2.get()<<"\n";
	std::cout<<"done thread3 "<<t3.get()<<"\n";
	return 0;
}
