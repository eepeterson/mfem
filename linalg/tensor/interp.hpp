// Copyright (c) 2010-2020, Lawrence Livermore National Security, LLC. Produced
// at the Lawrence Livermore National Laboratory. All Rights reserved. See files
// LICENSE and NOTICE for details. LLNL-CODE-806117.
//
// This file is part of the MFEM library. For more information and source code
// availability visit https://mfem.org.
//
// MFEM is free software; you can redistribute it and/or modify it under the
// terms of the BSD-3 license. We welcome feedback and contributions, see file
// CONTRIBUTING.md for details.

#ifndef MFEM_TENSOR_INTERP
#define MFEM_TENSOR_INTERP

#include "tensor.hpp"
#include "contraction.hpp"
#include "../../general/backends.hpp"
#include "../dtensor.hpp"
#include <utility>
#include "basis.hpp"
#include "contraction.hpp"

namespace mfem
{

// Non-tensor
template <int Dim, int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const Basis<Dim,false,D,Q> &basis, const Dofs &u)
{
   // TODO declare some __shared__/MFEM_SHARED memory for the basis?
   // Change GetB interface, Device struct don't work
   auto B = basis.GetB();
   return B * u;
}

// 1D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const Basis<1,true,D,Q> &basis, const Dofs &u)
{
   auto B = basis.GetB();
   return ContractX(B,u);
}

// 2D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const Basis<2,true,D,Q> &basis, const Dofs &u)
{
   auto B = basis.GetB();
   auto Bu = ContractX(B,u);
   return ContractY(B,Bu);
}

// 3D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const Basis<3,true,D,Q> &basis, const Dofs &u)
{
   auto B = basis.GetB();
   auto Bu = ContractX(B,u);
   auto BBu = ContractY(B,Bu);
   return ContractZ(B,BBu);
}

// Non-tensor
template <int Dim, int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const BasisTranspose<Dim,false,D,Q> &basis, const Dofs &u)
{
   auto Bt = basis.GetBt();
   return Bt * u;
}

// 1D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const BasisTranspose<1,true,D,Q> &basis, const Dofs &u)
{
   auto Bt = basis.GetBt();
   return ContractX(Bt,u);
}

// 2D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const BasisTranspose<2,true,D,Q> &basis, const Dofs &u)
{
   auto Bt = basis.GetBt();
   auto Bu = ContractY(Bt,u);
   return ContractX(Bt,Bu);
}

// 3D Tensor
template <int D, int Q, typename Dofs> MFEM_HOST_DEVICE inline
auto operator*(const BasisTranspose<3,true,D,Q> &basis, const Dofs &u)
{
   auto Bt = basis.GetBt();
   auto Bu = ContractZ(Bt,u);
   auto BBu = ContractY(Bt,Bu);
   return ContractX(Bt,BBu);
}

} // namespace mfem

#endif // MFEM_TENSOR_INTERP