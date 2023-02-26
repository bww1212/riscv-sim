main:                                   # @main
        addi    sp, sp, -32
        sw      ra, 28(sp)                      # 4-byte Folded Spill
        sw      s0, 24(sp)                      # 4-byte Folded Spill
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -12(s0)
        sw      a0, -16(s0)
        j       .LBB0_1
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
        lw      a1, -16(s0)
        li      a0, 9
        blt     a0, a1, .LBB0_4
        j       .LBB0_2
.LBB0_2:                                #   in Loop: Header=BB0_1 Depth=1
        lw      a0, -16(s0)
        call    fibint
        sw      a0, -20(s0)
        j       .LBB0_3
.LBB0_3:                                #   in Loop: Header=BB0_1 Depth=1
        lw      a0, -16(s0)
        addi    a0, a0, 1
        sw      a0, -16(s0)
        j       .LBB0_1
.LBB0_4:
        lw      a0, -12(s0)
        lw      ra, 28(sp)                      # 4-byte Folded Reload
        lw      s0, 24(sp)                      # 4-byte Folded Reload
        addi    sp, sp, 32
        ret
fibint:                                # @fib(int)
        addi    sp, sp, -32
        sw      ra, 28(sp)                      # 4-byte Folded Spill
        sw      s0, 24(sp)                      # 4-byte Folded Spill
        addi    s0, sp, 32
        sw      a0, -16(s0)
        lw      a1, -16(s0)
        li      a0, 1
        blt     a0, a1, .LBB1_2
        j       .LBB1_1
.LBB1_1:
        lw      a0, -16(s0)
        sw      a0, -12(s0)
        j       .LBB1_3
.LBB1_2:
        lw      a0, -16(s0)
        addi    a0, a0, -1
        call    fibint
        sw      a0, -20(s0)                     # 4-byte Folded Spill
        lw      a0, -16(s0)
        addi    a0, a0, -2
        call    fibint
        mv      a1, a0
        lw      a0, -20(s0)                     # 4-byte Folded Reload
        add     a0, a0, a1
        sw      a0, -12(s0)
        j       .LBB1_3
.LBB1_3:
        lw      a0, -12(s0)
        lw      ra, 28(sp)                      # 4-byte Folded Reload
        lw      s0, 24(sp)                      # 4-byte Folded Reload
        addi    sp, sp, 32
        ret
