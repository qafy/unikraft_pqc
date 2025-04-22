#!/usr/bin/env python

with open("pki/CA_dil.crt", "r") as f:
    lines = f.readlines() 
    output = ["static char *ca_certificate = "]
    for line in lines:
        output.append("\"" + line[:-1] + "\\n\"" + "\n")

    
    res = "".join(output) 
    res = res[:-1] + ";"
    with open("Unikraft/ssl_uk_test/certificate.h", "w") as fout:
        fout.write(res)