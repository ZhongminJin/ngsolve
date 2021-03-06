#ifndef FILE_SCALARFE
#define FILE_SCALARFE

/*********************************************************************/
/* File:   scalarfe.hpp                                              */
/* Author: Joachim Schoeberl                                         */
/* Date:   25. Mar. 2000                                             */
/*********************************************************************/

namespace ngfem
{
  
  class BaseScalarFiniteElement : public FiniteElement 
  {
  public:
    // using FiniteElement::FiniteElement;

    INLINE BaseScalarFiniteElement () { ; } 
    INLINE BaseScalarFiniteElement (int andof, int aorder)
      : FiniteElement (andof, aorder) { ; }


    /// compute shape
    HD NGS_DLL_HEADER 
    virtual void CalcShape (const IntegrationPoint & ip, 
                            BareSliceVector<> shape) const = 0;

    HD NGS_DLL_HEADER 
    virtual void CalcShape (const IntegrationPoint & ip, 
                            BareSliceVector<Complex> shape) const;
    
    /// compute dshape, matrix: ndof x spacedim
    HD NGS_DLL_HEADER 
    virtual void CalcDShape (const IntegrationPoint & ip, 
			     SliceMatrix<> dshape) const = 0;
    

    /**
       returns shape functions in point ip.
    */
    INLINE FlatVector<> GetShape (const IntegrationPoint & ip, 
				  LocalHeap & lh) const
    {
      FlatVector<> shape(ndof, lh);
      CalcShape (ip, shape);
      return shape;
    }

    /// compute shape, row is shape nr, col is ip nr
    HD NGS_DLL_HEADER 
    virtual void CalcShape (const IntegrationRule & ir, 
                            SliceMatrix<> shape) const;
  
    /// compute shape, row is shape nr, col is ip nr
    HD NGS_DLL_HEADER 
    virtual void CalcShape (const SIMD_IntegrationRule & ir, 
                            BareSliceMatrix<SIMD<double>> shape) const;

    // rows dim*ndof, cols .. nip
    // rows:  phi0/dx, phi0/dy, phi0/dz, phi1/dx ... 
    HD NGS_DLL_HEADER 
    virtual void CalcMappedDShape (const SIMD_BaseMappedIntegrationRule & mir, 
                                   BareSliceMatrix<SIMD<double>> dshapes) const;

    
    /**
       Evaluates function in integration point ip.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual double Evaluate (const IntegrationPoint & ip, BareSliceVector<> x) const;


    /**
       Evaluate function in points of integrationrule ir.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual void Evaluate (const IntegrationRule & ir, BareSliceVector<> coefs, FlatVector<> values) const;
    HD NGS_DLL_HEADER virtual void Evaluate (const SIMD_IntegrationRule & ir, BareSliceVector<> coefs, BareVector<SIMD<double>> values) const;
    HD NGS_DLL_HEADER virtual void Evaluate (const SIMD_IntegrationRule & ir, SliceMatrix<> coefs, BareSliceMatrix<SIMD<double>> values) const;

    /**
       Each column a vector ...
     */
    HD NGS_DLL_HEADER virtual void Evaluate (const IntegrationRule & ir, SliceMatrix<> coefs, SliceMatrix<> values) const;
    
    /**
       Evaluate function in points of integrationrule ir, transpose operation.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual void EvaluateTrans (const IntegrationRule & ir, FlatVector<> values, BareSliceVector<> coefs) const;
    HD NGS_DLL_HEADER virtual void AddTrans (const SIMD_IntegrationRule & ir, BareVector<SIMD<double>> values, BareSliceVector<> coefs) const;
    HD NGS_DLL_HEADER virtual void AddTrans (const SIMD_IntegrationRule & ir, BareSliceMatrix<SIMD<double>> values, SliceMatrix<> coefs) const;

    HD NGS_DLL_HEADER virtual void EvaluateGrad (const SIMD_BaseMappedIntegrationRule & ir, BareSliceVector<> coefs, BareSliceMatrix<SIMD<double>> values) const;
    // needed for ALE-trafo
    HD NGS_DLL_HEADER virtual void EvaluateGrad (const SIMD_IntegrationRule & ir, BareSliceVector<> coefs, BareSliceMatrix<SIMD<double>> values) const;
    HD NGS_DLL_HEADER virtual void AddGradTrans (const SIMD_BaseMappedIntegrationRule & ir, BareSliceMatrix<SIMD<double>> values,
                                                 BareSliceVector<> coefs) const;

    
  };

  /**
     Scalar finite element.
     Provides shape functions and derivatives.
  */
  template <int D>
  class ScalarFiniteElement : public BaseScalarFiniteElement
  {
  public:
    using BaseScalarFiniteElement::BaseScalarFiniteElement;

    /// the name
    NGS_DLL_HEADER virtual string ClassName() const;

    HD NGS_DLL_HEADER virtual int Dim () const { return D; }


    /**
       returns derivatives in point ip.
    */
    INLINE const FlatMatrixFixWidth<D> 
    GetDShape (const IntegrationPoint & ip, LocalHeap & lh) const
    {
      FlatMatrixFixWidth<D> dshape(ndof, lh);
      CalcDShape (ip, dshape);
      return dshape;
    }

    using BaseScalarFiniteElement::CalcShape;
    using BaseScalarFiniteElement::CalcDShape;
    using BaseScalarFiniteElement::CalcMappedDShape;    

    

    /// compute dshape, matrix: ndof x spacedim
    HD NGS_DLL_HEADER 
    virtual void CalcMappedDShape (const MappedIntegrationPoint<D,D> & mip, 
                                   SliceMatrix<> dshape) const;


    HD NGS_DLL_HEADER 
    virtual void CalcMappedDShape (const MappedIntegrationRule<D,D> & mir, 
                                   SliceMatrix<> dshapes) const;




    /**
       returns second derivatives in point ip.
       returns stored values for valid ip.IPNr(), else computes values
    */
    const FlatMatrix<> GetDDShape (const IntegrationPoint & ip, LocalHeap & lh) const
    {
      FlatMatrix<> ddshape(ndof, D*D, lh);
      CalcDDShape (ip, ddshape);
      return ddshape;
    }

    /// compute dshape, matrix: ndof x (spacedim spacedim)
    NGS_DLL_HEADER virtual void CalcDDShape (const IntegrationPoint & ip, 
                                             FlatMatrix<> ddshape) const;
    
    /// compute dshape, matrix: ndof x (spacedim spacedim)
    NGS_DLL_HEADER virtual void CalcMappedDDShape (const MappedIntegrationPoint<D,D> & mip, 
                                                   SliceMatrix<> ddshape) const;



    /**
       Evaluates gradient in integration point ip.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual Vec<D> EvaluateGrad (const IntegrationPoint & ip, BareSliceVector<> x) const;

    using BaseScalarFiniteElement::Evaluate;
    using BaseScalarFiniteElement::EvaluateGrad;
    using BaseScalarFiniteElement::AddGradTrans;

    /**
       Evaluate gradient in points of integrationrule ir.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual void EvaluateGrad (const IntegrationRule & ir, BareSliceVector<> coefs, FlatMatrixFixWidth<D> values) const;
    
    /**
       Evaluate gradient in points of integrationrule ir, transpose operation.
       Vector x provides coefficient vector.
     */
    HD NGS_DLL_HEADER virtual void EvaluateGradTrans (const IntegrationRule & ir, FlatMatrixFixWidth<D> values, BareSliceVector<> coefs) const;

    HD NGS_DLL_HEADER virtual void EvaluateGradTrans (const IntegrationRule & ir, SliceMatrix<> values, SliceMatrix<> coefs) const;

    HD NGS_DLL_HEADER virtual void GetPolOrders (FlatArray<PolOrder<D> > orders) const;

  public:
    NGS_DLL_HEADER virtual std::list<std::tuple<std::string,double>> Timing () const;
  };




















  template<int D>
  class DGFiniteElement : public ScalarFiniteElement<D>
  {
  protected:
    int vnums[1<<D];  

    using ScalarFiniteElement<D>::ndof;
    using ScalarFiniteElement<D>::order;

  public:
    /// global vertex numbers define ordering of vertices
    template <typename TA>
    void SetVertexNumbers (const TA & avnums)
    { 
      for (int i = 0; i < avnums.Size(); i++) vnums[i] = avnums[i]; 
    }

    /// assign vertex number
    void SetVertexNumber (int nr, int vnum) { vnums[nr] = vnum; }
    NGS_DLL_HEADER virtual void SetOrder (INT<D> p) = 0;
    NGS_DLL_HEADER virtual void ComputeNDof() = 0;


    NGS_DLL_HEADER virtual void PrecomputeTrace () = 0; 
    NGS_DLL_HEADER virtual void PrecomputeGrad () = 0;

    NGS_DLL_HEADER void CalcTraceMatrix (int facet, FlatMatrix<> trace) const;
    NGS_DLL_HEADER void CalcGradientMatrix (FlatMatrix<> gmat) const;

    HD NGS_DLL_HEADER virtual void GetDiagMassMatrix (FlatVector<> mass) const;

    NGS_DLL_HEADER virtual void GetGradient (FlatVector<> coefs, FlatMatrixFixWidth<D> grad) const;
    NGS_DLL_HEADER virtual void GetGradientTrans (FlatMatrixFixWidth<D> grad, FlatVector<> coefs) const;

    NGS_DLL_HEADER virtual void GetTrace (int facet, FlatVector<> coefs, FlatVector<> fcoefs) const;
    NGS_DLL_HEADER virtual void GetTraceTrans (int facet, FlatVector<> fcoefs, FlatVector<> coefs) const;
  };
  



#ifdef FILE_SCALARFE_CPP
#define SCALARFE_EXTERN
#else
#define SCALARFE_EXTERN extern

  SCALARFE_EXTERN template class ScalarFiniteElement<0>;
  SCALARFE_EXTERN template class ScalarFiniteElement<1>;
  SCALARFE_EXTERN template class ScalarFiniteElement<2>;
  SCALARFE_EXTERN template class ScalarFiniteElement<3>;

  SCALARFE_EXTERN template class DGFiniteElement<0>;
  SCALARFE_EXTERN template class DGFiniteElement<1>;
  SCALARFE_EXTERN template class DGFiniteElement<2>;
  SCALARFE_EXTERN template class DGFiniteElement<3>;

#endif
}

#endif
