## cpufeat
A small tool to know if your CPU support several modern x86_64 instructions.

## Usage
By default there's no parameter needed, however, you can still use `--help` to get this.
```
cpufeat

Usage:
   --features      -- Output several relevant CPU features (default)
   --vendor        -- Output CPU vendor
```

## Note
Make sure your CPU does support `cpuid` instruction.
// TODO: Specify first Intel CPU that does support `cpuid` and extended eax
