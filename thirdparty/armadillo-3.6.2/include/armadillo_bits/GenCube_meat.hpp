// Copyright (C) 2011 NICTA (www.nicta.com.au)
// Copyright (C) 2011 Conrad Sanderson
// 
// This file is part of the Armadillo C++ library.
// It is provided without any warranty of fitness
// for any purpose. You can redistribute this file
// and/or modify it under the terms of the GNU
// Lesser General Public License (LGPL) as published
// by the Free Software Foundation, either version 3
// of the License or (at your option) any later version.
// (see http://www.opensource.org/licenses for more info)


//! \addtogroup Gen
//! @{



template<typename eT, typename gen_type>
arma_inline
GenCube<eT, gen_type>::GenCube(const uword in_n_rows, const uword in_n_cols, const uword in_n_slices)
  : n_rows  (in_n_rows  )
  , n_cols  (in_n_cols  )
  , n_slices(in_n_slices)
  {
  arma_extra_debug_sigprint();
  }



template<typename eT, typename gen_type>
arma_inline
GenCube<eT, gen_type>::~GenCube()
  {
  arma_extra_debug_sigprint();
  }



template<typename eT, typename gen_type>
arma_inline
eT
GenCube<eT, gen_type>::generate()
  {
       if(is_same_type<gen_type, gen_ones_full>::value == true) { return eT(1);                   }
  else if(is_same_type<gen_type, gen_zeros    >::value == true) { return eT(0);                   }
  else if(is_same_type<gen_type, gen_randu    >::value == true) { return eT(eop_aux_randu<eT>()); }
  else if(is_same_type<gen_type, gen_randn    >::value == true) { return eT(eop_aux_randn<eT>()); }
  else                                                          { return eT();                    }
  }



template<typename eT, typename gen_type>
arma_inline
eT
GenCube<eT, gen_type>::operator[](const uword) const
  {
  return GenCube<eT, gen_type>::generate();
  }



template<typename eT, typename gen_type>
arma_inline
eT
GenCube<eT, gen_type>::at(const uword, const uword, const uword) const
  {
  return GenCube<eT, gen_type>::generate();
  }



template<typename eT, typename gen_type>
inline
void
GenCube<eT, gen_type>::apply(Cube<eT>& out) const
  {
  arma_extra_debug_sigprint();
  
  // NOTE: we're assuming that the cube has already been set to the correct size;
  // this is done by either the Cube contructor or operator=()
  
       if(is_same_type<gen_type, gen_ones_full>::value == true) { out.ones();  }
  else if(is_same_type<gen_type, gen_zeros    >::value == true) { out.zeros(); }
  else if(is_same_type<gen_type, gen_randu    >::value == true) { out.randu(); }
  else if(is_same_type<gen_type, gen_randn    >::value == true) { out.randn(); }
  }



template<typename eT, typename gen_type>
inline
void
GenCube<eT, gen_type>::apply_inplace_plus(Cube<eT>& out) const
  {
  arma_extra_debug_sigprint();
  
  arma_debug_assert_same_size(out.n_rows, out.n_cols, out.n_slices, n_rows, n_cols, n_slices, "addition");
  
  
        eT*   out_mem = out.memptr();
  const uword n_elem  = out.n_elem;
  
  uword i,j;
  
  for(i=0, j=1; j<n_elem; i+=2, j+=2)
    {
    const eT tmp_i = GenCube<eT, gen_type>::generate();
    const eT tmp_j = GenCube<eT, gen_type>::generate();
    
    out_mem[i] += tmp_i;
    out_mem[j] += tmp_j;
    }
  
  if(i < n_elem)
    {
    out_mem[i] += GenCube<eT, gen_type>::generate();
    }
  }




template<typename eT, typename gen_type>
inline
void
GenCube<eT, gen_type>::apply_inplace_minus(Cube<eT>& out) const
  {
  arma_extra_debug_sigprint();
  
  arma_debug_assert_same_size(out.n_rows, out.n_cols, out.n_slices, n_rows, n_cols, n_slices, "subtraction");
  
  
        eT*   out_mem = out.memptr();
  const uword n_elem  = out.n_elem;
  
  uword i,j;
  
  for(i=0, j=1; j<n_elem; i+=2, j+=2)
    {
    const eT tmp_i = GenCube<eT, gen_type>::generate();
    const eT tmp_j = GenCube<eT, gen_type>::generate();
    
    out_mem[i] -= tmp_i;
    out_mem[j] -= tmp_j;
    }
  
  if(i < n_elem)
    {
    out_mem[i] -= GenCube<eT, gen_type>::generate();
    }
  }




template<typename eT, typename gen_type>
inline
void
GenCube<eT, gen_type>::apply_inplace_schur(Cube<eT>& out) const
  {
  arma_extra_debug_sigprint();
  
  arma_debug_assert_same_size(out.n_rows, out.n_cols, out.n_slices, n_rows, n_cols, n_slices, "element-wise multiplication");
  
  
        eT*   out_mem = out.memptr();
  const uword n_elem  = out.n_elem;
  
  uword i,j;
  
  for(i=0, j=1; j<n_elem; i+=2, j+=2)
    {
    const eT tmp_i = GenCube<eT, gen_type>::generate();
    const eT tmp_j = GenCube<eT, gen_type>::generate();
    
    out_mem[i] *= tmp_i;
    out_mem[j] *= tmp_j;
    }
  
  if(i < n_elem)
    {
    out_mem[i] *= GenCube<eT, gen_type>::generate();
    }
  }




template<typename eT, typename gen_type>
inline
void
GenCube<eT, gen_type>::apply_inplace_div(Cube<eT>& out) const
  {
  arma_extra_debug_sigprint();
  
  arma_debug_assert_same_size(out.n_rows, out.n_cols, out.n_slices, n_rows, n_cols, n_slices, "element-wise division");
  
  
        eT*   out_mem = out.memptr();
  const uword n_elem  = out.n_elem;
  
  uword i,j;
  
  for(i=0, j=1; j<n_elem; i+=2, j+=2)
    {
    const eT tmp_i = GenCube<eT, gen_type>::generate();
    const eT tmp_j = GenCube<eT, gen_type>::generate();
    
    out_mem[i] /= tmp_i;
    out_mem[j] /= tmp_j;
    }
  
  if(i < n_elem)
    {
    out_mem[i] /= GenCube<eT, gen_type>::generate();
    }
  }




//! @}
