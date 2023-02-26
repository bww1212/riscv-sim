main:                                   # @main
        addi    sp, sp, -32
        sw      ra, 28(sp)                      # 4-byte Folded Spill
        sw      s0, 24(sp)                      # 4-byte Folded Spill
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -12(s0)
        li      a0, 1
        sw      a0, -16(s0)
        li      a1, 2
        sw      a1, -20(s0)
        sw      a0, -28(s0)
        j       .LBB0_1
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
        lw      a1, -28(s0)
        li      a0, 10
        blt     a0, a1, .LBB0_4
        j       .LBB0_2
.LBB0_2:                                #   in Loop: Header=BB0_1 Depth=1
        lw      a0, -16(s0)
        lw      a1, -20(s0)
        add     a0, a0, a1
        sw      a0, -24(s0)
        lw      a0, -20(s0)
        sw      a0, -16(s0)
        lw      a0, -24(s0)
        sw      a0, -20(s0)
        j       .LBB0_3
.LBB0_3:                                #   in Loop: Header=BB0_1 Depth=1
        lw      a0, -28(s0)
        addi    a0, a0, 1
        sw      a0, -28(s0)
        j       .LBB0_1
.LBB0_4:
        li      a0, 0
        lw      ra, 28(sp)                      # 4-byte Folded Reload
        lw      s0, 24(sp)                      # 4-byte Folded Reload
        addi    sp, sp, 32
        ret
