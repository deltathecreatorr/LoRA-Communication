import sys, pathlib

src = pathlib.Path(sys.argv[1])
data = src.read_bytes()
name = src.stem.replace("-", "_")

lines = ["#pragma once", "#include <cstdint>", "#include <cstddef>", "",
         f"static const uint8_t {name}_png[] = {{"]
for i in range(0, len(data), 16):
    chunk = ", ".join(f"0x{b:02x}" for b in data[i:i + 16])
    lines.append(f"    {chunk},")
lines += ["};", f"static const size_t {name}_png_len = {len(data)};", ""]

src.with_suffix(".h").write_text("\n".join(lines))