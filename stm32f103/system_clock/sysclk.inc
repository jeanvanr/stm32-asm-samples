@ setup core clock to 72 MHz
@ Steps:
@ enable HSE => wait for HSE activation => setup PLL => activate PLL => wait for PLL activation => configure flash => switch to PLL

section_system_clock_init:
    mov32 r1, 0x40021000       @ RCC_CR address
    ldr   r0, [r1]
    orr   r0, r0, #0x00010000  @ Enable HSE
    str   r0, [r1]

    @ while (!HSE_ready);
ssci_l0:
    ldr   r0, [r1]
    tst   r0, #0x00020000
    bne   ssci_l0

    @ setup PLL
    mov32 r1, 0x40021004       @ RCC_CFGR address
    ldr   r0, [r1]
    orr   r0, r0, #0x001c0000  @ set PLLMUL to 9 (9 * 8 MHz = 72 MHz)
    str   r0, [r1]

    ldr   r0, [r1]
    orr   r0, r0, #0x00000400  @ set APB1 div to 2 (72 MHz / 2 = 36 MHz (36 MHz max for APB1))
    str   r0, [r1]

    ldr   r0, [r1]
    orr   r0, r0, #0x00010000  @ select PLLSRC (HSE as PLL source)
    str   r0, [r1]

    @ activate PLL
    mov32 r1, 0x40021000       @ RCC_CR address
    ldr   r0, [r1]
    orr   r0, r0, #0x01000000  @ Enable PLL
    str   r0, [r1]

    @ while (!PLL_ready);
ssci_l1:
    ldr   r0, [r1]
    tst   r0, #0x02000000
    bne   ssci_l1
<<<<<<< HEAD

=======
    
>>>>>>> f351f9d6437c272fae911f33e4aa849c33ce4325
    @ configure flash latency
    mov32 r1, 0x40022000       @ FLASH_ACR address
    mov32 r0, 0x00000001       @ set flash wait state
    str   r0, [r1]

    @ PLL as clock source
    mov32 r1, 0x40021004       @ RCC_CFGR address
    ldr   r0, [r1]
    orr   r0, r0, #0x00000002  @ system clock source is PLL
    str   r0, [r1]
