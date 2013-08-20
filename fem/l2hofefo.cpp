/*********************************************************************/
/* File:   l2hofe.cpp                                                */
/* Author: Start                                                      */
/* Date:   6. Feb. 2003                                              */
/*********************************************************************/

#define FILE_L2HOFEFO_CPP

 
#include <fem.hpp>
#include "l2hofe.hpp"
#include "l2hofefo.hpp"
#include "l2hofe_impl.hpp"
#include <tscalarfe_impl.hpp>

namespace ngfem
{

  template <int ORDER>
  PrecomputedShapesContainer<PrecomputedScalShapes<2> > L2HighOrderFEFO_Shapes<ET_TRIG, ORDER>::precomp;



  /*
  template <int ORDER>
  PrecomputedShapesContainer<PrecomputedScalShapes<2> > L2HighOrderFEFO<ET_TRIG, ORDER>::precomp;

  template class T_L2HighOrderFiniteElementFO<ET_TRIG,0>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,1>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,2>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,3>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,4>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,5>;
  template class T_L2HighOrderFiniteElementFO<ET_TRIG,6>;


  template class L2HighOrderFEFO<ET_TRIG,0>;
  template class L2HighOrderFEFO<ET_TRIG,1>;
  template class L2HighOrderFEFO<ET_TRIG,2>;
  template class L2HighOrderFEFO<ET_TRIG,3>;
  template class L2HighOrderFEFO<ET_TRIG,4>;
  template class L2HighOrderFEFO<ET_TRIG,5>; 
  template class L2HighOrderFEFO<ET_TRIG,6>;

  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,0>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,1>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,2>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,3>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,4>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,5>, ET_TRIG>;
  template class T_ScalarFiniteElement2<L2HighOrderFEFO<ET_TRIG,6>, ET_TRIG>;
  */
}
 
