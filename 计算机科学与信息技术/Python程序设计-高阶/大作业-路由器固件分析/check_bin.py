import binwalk

# Equivalent to: 'binwalk --signature firmware1.bin firmware2.bin'.
# Note the use of 'quiet=True' to suppress normal binwalk output.
for module in binwalk.scan('./openwrt-11.19.2023-ramips-mt7621-linksys_e5600-squashfs-factory.bin',
                           signature=True,
                           quiet=True):

    # binwalk.scan returns a module object for every executed
    # module; in this case, there should be only one, which is
    # the signature module.
    print("%s Results:" % module.name)

    # Each module has a list of result objects, describing
    # the results returned from the executed module.
    ans: str = ''
    for result in module.results:
        print("\t%s    0x%.8X    %s" % (result.file.name,
                                        result.offset,
                                        result.description))
        ans += "0x%.8X    %s" % (result.offset, result.description) + '\n'

    with open("signature_result.txt", "w"):
        print(ans, file=open("signature_result.txt", "w"))
