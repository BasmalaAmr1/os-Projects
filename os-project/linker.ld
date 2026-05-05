ENTRY(start) [cite: 245]

SECTIONS {
    . = 1M;    /* تحميل الكرنل عند عنوان 1 ميجابايت */ [cite: 247, 261]

    .boot :
    {
        *(.multiboot_header) [cite: 250]
    }

    .text :
    {
        *(.text) [cite: 254]
    }
}