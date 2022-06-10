#include <map>
#include <iostream>
#include <string>


typedef void* (*PTRCreateObject)(void);  

class ClassFactory {
private:  
    std::map<std::string, PTRCreateObject> m_classMap ;  
	ClassFactory(){}; //构造函数私有化
	
public:   
    void* getClassByName(std::string className);  
    void registClass(std::string name, PTRCreateObject method) ;  
    static ClassFactory& getInstance() ;  
};

void* ClassFactory::getClassByName(std::string className){  
    std::map<std::string, PTRCreateObject>::const_iterator iter;  
    iter = m_classMap.find(className) ;  
    if ( iter == m_classMap.end() )  
        return NULL ;  
    else  
        return iter->second() ;  
}  
   
void ClassFactory::registClass(std::string name, PTRCreateObject method){  
    m_classMap.insert(std::pair<std::string, PTRCreateObject>(name, method)) ;  
}  
   
ClassFactory& ClassFactory::getInstance(){
    // it's not thread safe in c++03
    // https://stackoverflow.com/questions/19130021/how-to-declare-an-static-instance-of-a-class-in-c
    static ClassFactory sLo_factory;  
    return sLo_factory ;  
}  

class RegisterAction{
public:
	RegisterAction(std::string className,PTRCreateObject ptrCreateFn){
		ClassFactory::getInstance().registClass(className,ptrCreateFn);
	}
};

#define REGISTER(className) 											\
	className* objectCreator##className(){     							\
        return new className;                                         	\
    }                                                                  	\
    RegisterAction g_creatorRegister##className(                        \
		#className,(PTRCreateObject)objectCreator##className)

// test class
class TestClass {
public:
	virtual void m_print() = 0;
};

// test class A
class TestClassA: public TestClass {
public:
	void m_print() {
		std::cout << "hello TestClassA" << std::endl;
	};
};
REGISTER(TestClassA);

// test class B
class TestClassB: public TestClass {
public:
	void m_print() {
		std::cout << "hello TestClassB" << std::endl;
	};
};
REGISTER(TestClassB);

int main(int argc,char* argv[]) {
	TestClass* ptrObjA = (TestClassA*)ClassFactory::getInstance().getClassByName("TestClassA");
	ptrObjA->m_print();

    TestClass* ptrObjB = (TestClassB*)ClassFactory::getInstance().getClassByName("TestClassB");
	ptrObjB->m_print();

    return 0;
}
