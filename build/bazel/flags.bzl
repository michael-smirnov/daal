
# Always flags

# Opt flags
# -O2
# -D_FORTIFY_SOURCE=2

# Dbg flags
# -g
# -DDEBUG_ASSERT

lnx_cc_common_flags = [
    "-fwrapv",
    "-fstack-protector-strong",
    "-fno-strict-overflow",
    "-fno-delete-null-pointer-checks",
    "-Wall",
    "-Wextra",
    "-Wformat",
    "-Wformat-security",
    "-Werror=unknown-pragmas",
    "-Werror=uninitialized",
    "-Werror=return-type",
    "-Wno-unused-parameter",
    "-pedantic",
]

def get_default_flags(arch_id, os_id, compiler_id):
    arch_flags = {
        "ia32": ["-m32"],
        "intel64": ["-m64"],
    }[arch_id]
    return (
        arch_flags +
        lnx_cc_common_flags
    )


def get_cpu_flags(arch_id, os_id, compiler_id):
    cpu_flag_pattern = "-march={}"
    if compiler_id == "gcc":
        cpu_flags = {
            "sse2":       "pentium4" if arch_id == "ia32" else "nocona",
            "ssse3":      "pentium4" if arch_id == "ia32" else "nocona",
            "sse42":      "corei7",
            "avx":        "sandybridge",
            "avx2":       "haswell",
            "avx512_mic": "haswell",
            "avx512":     "haswell",
        }
    return { k: cpu_flag_pattern.format(v) for k, v in cpu_flags.items() }