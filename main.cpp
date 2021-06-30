static const unsigned short MEM_START = 512, MEM_MAX = 4096, W = 64, H = 32;

struct chip8
{
    unsigned char mem[MEM_MAX], dsp[W * H];
    unsigned char v[16], snd_tmr, dly_tmr, sp, keys[16];
    unsigned short i, pc, stack[16];

    void load_font()
    {
        const unsigned char fonts[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 
            0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
            0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0,
            0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40,
            0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0, 0x10, 0xF0,
            0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
            0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 
            0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80  
        };

        auto *p = fonts;

        for (int i = 512; i < 512 + (16*5); ++i, ++p)
        {
            mem[i] = *p;
        }
    }

    void reset()
    {
        pc = 0, snd_tmr = 0, dly_tmr = 0, sp = 0, i = 0;
        for (int i = 0; i < 16; i++) v[i] = 0, stack[i];
        for (int i = 0; i < 62*32; i++) dsp[i] = 0;
        for (int i = 0; i < 4096; i++) mem[i] = 0;
    }

    void initialize()
    {
        reset();
        load_font();
    }

    void cycle()
    {
        unsigned short opcode;
        
        if (opcode & 0xF000) {
            switch (opcode) {
                // JMP
                case 0x1000:
                    pc = opcode & 0x0FFF;
                    break;
                
                // CALL
                case 0x2000:
                    ++sp;
                    stack[sp] = pc;
                    pc = 0x0FFF;
                    break;
                
                // SE vx, byte
                case 0x3000:
                    if (v[opcode & 0x0F00] = opcode & 0x00FF) ++pc;
                    break;
                
                // SNE vx, byte
                case 0x4000:
                    if (v[opcode & 0x0F00] != opcode & 0x00FF) ++pc;
                    break;
                
                // SE vx, vy
                case 0x5000:
                    if (v[opcode & 0x0F00] = v[opcode & 0x00F0]) ++pc;
                    break;

                // LD vx, byte
                case 0x6000:
                    if (v[opcode & 0x0F00] = opcode & 0x00FF);
                    break;

                // ADD vx, byte
                case 0x7000:
                    if (v[opcode & 0x0F00] += opcode & 0x00FF);
                    break;

                // LD vx, vy
                case 0x8000:
                    switch (opcode & 0x000F)
                    {
                    case 0x0001:
                        v[opcode & 0x0F00] |= v[opcode & 0x00F0];
                        break;
                    
                    case 0x0002:
                        v[opcode & 0x0F00] &= v[opcode & 0x00F0];
                        break;

                    case 0x0003:
                        v[opcode & 0x0F00] |= ~v[opcode & 0x00F0];
                        break;

                    default:
                        break;
                    }

                default:
                    break;
            }
        } else {
            switch (opcode) {

                // CLS
                case 0x00E0:
                    for (int i = 0; i < W * H; i++) dsp[i] = 0;
                    break;
                
                // RET
                case 0x00EE:
                    pc = stack[16];
                    --sp;
                    break;  
            }
        }
    }
};

int main() 
{
    return 0;
}