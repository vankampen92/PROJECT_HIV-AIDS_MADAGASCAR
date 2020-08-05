#include <MODEL.h>

void assert_right_model_definition( Parameter_Table * P )
{

#if defined XWSILD
  #if defined YSILD
    assert ( P->TYPE_of_MODEL == 0 );
  #endif
#endif

#if defined X2W2SILD
  #if defined YSILD
    assert( P->TYPE_of_MODEL == 1 );
  #endif
#endif

#if defined X_
  #if defined Y_
    assert( P->TYPE_of_MODEL == 2 );
  #endif
#endif

#if defined X2W2
  #if defined Y_
    assert( P->TYPE_of_MODEL == 3 );
  #endif
#endif

}
