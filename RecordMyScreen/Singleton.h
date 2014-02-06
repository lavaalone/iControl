#ifndef __SINGLETON_H_
#define __SINGLETON_H_

template <class T> class CSingleton
{
	private:
		CSingleton(const CSingleton&);
		CSingleton& operator = (const CSingleton&);
	protected:
		CSingleton(){}
	public:
		static T* GetInstance()
		{	
			static T instance;
			return &instance;
		}
};

#endif
