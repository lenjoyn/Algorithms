#include"iostream"
#include"thread"
void RunFunction(){

     std::cout<<"testing function\n";
}

class RunFunctor{
public:
	void operator()(){
		std::cout<<"testing functor\n";
	}
};

auto RunLambda = []{std::cout<<"testing Lambda\n";};


int main(){


	std::thread t1(RunFunction);
	RunFunctor func;
	std::thread t2(func);
	std::thread t3(RunLambda);

	t1.join();
	t2.join();
	t3.join();

	std::cout<<"jobs are done"<<std::endl;

	return 0;
}
