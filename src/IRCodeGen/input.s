	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1"
	.file	"input.c"
	.globl	function                        # -- Begin function function
	.p2align	2
	.type	function,@function
function:                               # @function
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	sw	a1, -16(s0)
	lw	a0, -12(s0)
	lw	a1, -16(s0)
	add	a0, a0, a1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	function, .Lfunc_end0-function
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 32
	li	a0, 0
	sw	a0, -28(s0)                     # 4-byte Folded Spill
	sw	a0, -12(s0)
	li	a0, 10
	sw	a0, -16(s0)
	li	a0, 20
	sw	a0, -20(s0)
	lw	a0, -16(s0)
	lw	a1, -20(s0)
	call	function
	mv	a1, a0
	lw	a0, -28(s0)                     # 4-byte Folded Reload
	sw	a1, -24(s0)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
                                        # -- End function
	.ident	"Homebrew clang version 19.1.7"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym function
