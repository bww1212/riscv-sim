main:                                   # @main
        addi    sp, sp, -32
        sw      ra, 28(sp)                      # 4-byte Folded Spill
        sw      s0, 24(sp)                      # 4-byte Folded Spill
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -12(s0)
        li      a0, 1
        sw      a0, -16(s0)
        li      a0, 2
        sw      a0, -20(s0)
        lw      a0, -16(s0)
        lw      a1, -20(s0)
        sub     a0, a0, a1
        addi    a0, a0, 3
        sw      a0, -24(s0)
        lw      a1, -24(s0)
        lw      a0, -16(s0)
        bge     a0, a1, .LBB0_2
        j       .LBB0_1
.LBB0_1:
        li      a0, 4
        sw      a0, -28(s0)
        lw      a0, -28(s0)
        sw      a0, -12(s0)
        j       .LBB0_7
.LBB0_2:
        li      a0, 0
        sw      a0, -32(s0)
        j       .LBB0_3
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
        lw      a1, -32(s0)
        li      a0, 9
        blt     a0, a1, .LBB0_6
        j       .LBB0_4
.LBB0_4:                                #   in Loop: Header=BB0_3 Depth=1
        lw      a0, -16(s0)
        addi    a0, a0, 1
        sw      a0, -16(s0)
        j       .LBB0_5
.LBB0_5:                                #   in Loop: Header=BB0_3 Depth=1
        lw      a0, -32(s0)
        addi    a0, a0, 1
        sw      a0, -32(s0)
        j       .LBB0_3
.LBB0_6:
        lw      a0, -16(s0)
        sw      a0, -12(s0)
        j       .LBB0_7
.LBB0_7:
        lw      a0, -12(s0)
        lw      ra, 28(sp)                      # 4-byte Folded Reload
        lw      s0, 24(sp)                      # 4-byte Folded Reload
        addi    sp, sp, 32
        ret