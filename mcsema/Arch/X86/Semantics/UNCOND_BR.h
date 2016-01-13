/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef MCSEMA_ARCH_X86_SEMANTICS_UNCOND_BR_H_
#define MCSEMA_ARCH_X86_SEMANTICS_UNCOND_BR_H_

namespace {

template <typename T>
DEF_SEM(JMP, T target_pc) {
  W(state.gpr.rip) = static_cast<PC>(target_pc);
}

template <typename T>
DEF_SEM(INDIRECT_JMP, T target_pc) {
  W(state.gpr.rip) = static_cast<PC>(R(target_pc));
}

}  // namespace

DEF_ISEL_32or64(JMP_RELBRd, JMP<PC>);
DEF_ISEL_32or64(JMP_RELBRz, JMP<PC>);
DEF_ISEL_32or64(JMP_RELBRb, JMP<PC>);

#if 64 == ADDRESS_SIZE_BITS
DEF_ISEL(JMP_MEMv_64) = INDIRECT_JMP<M64>;
DEF_ISEL(JMP_GPRv_64) = INDIRECT_JMP<R64>;
#else
DEF_ISEL(JMP_MEMv_16) = INDIRECT_JMP<M16>;
DEF_ISEL(JMP_MEMv_32) = INDIRECT_JMP<M32>;

DEF_ISEL(JMP_GPRv_16) = INDIRECT_JMP<R16>;
DEF_ISEL(JMP_GPRv_32) = INDIRECT_JMP<R32>;
#endif

/*
625 XABORT XABORT_IMMb UNCOND_BR RTM RTM ATTRIBUTES:

1807 JMP_FAR JMP_FAR_MEMp2 UNCOND_BR BASE I86 ATTRIBUTES: FAR_XFER NOTSX SCALABLE
1808 JMP_FAR JMP_FAR_PTRp_IMMw UNCOND_BR BASE I86 ATTRIBUTES: FAR_XFER NOTSX SCALABLE
 */

#endif  // MCSEMA_ARCH_X86_SEMANTICS_UNCOND_BR_H_
