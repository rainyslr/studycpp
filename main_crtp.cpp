#include"crtp.h"
int main()
{
	derived_1 de11;
	derived_2 de21;
	base<derived_1> b1;
	base<derived_1>  &rbase=b1,*pbase = &de11;
	base<derived_2> &rbase2=de21;
	/*b1.static_implementation();
	b1.implementation();
	b1.static_interface();
	b1.interface();
	//pbase->static_implementation();
	//pbase->implementation();*/
	rbase2.implementation();
	rbase2.static_implementation();
    //de11.implementation();
	//de11.static_implementation();
	//de21.implementation();
	//de21.static_implementation();
        
	return 0;
}
