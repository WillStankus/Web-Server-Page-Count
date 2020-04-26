# Regular Requests

### Input

The Regular Company is managing three web servers each with their own subdomain (**mordecai**, **rigby**, **benson**). Provided is a small snippet of web requests made to these servers in the `requests.csv` file:

```
source,method,url
228.226.19.38,GET,https://benson.regular.host/jtucvp/wrhbdqgt/pskwfo/favicon.ico
180.183.190.107,GET,https://benson.regular.host/plyuag/zadhtbmq/hqoznrl/stats.html
57.119.26.193,GET,https://mordecai.regular.host/fzjena/nwjrlqu/demnb/stats.html
92.114.68.124,GET,https://benson.regular.host/rypbnk/rvgipdb/favicon.ico
106.130.107.157,GET,https://rigby.regular.host/kwluob/fdgblk/stats.html
74.67.18.218,GET,https://mordecai.regular.host/ntvbx/iqwzjda/stats.html
```

The company is interested in knowing how many times a certain file was requested on each of the subdomains.

### Output

Filter the `requests.csv` file so that all GET requests to a specific subdomain and file are counted (ignore all lines with POST method). For example, the above lines should generate the output:

```
$ ./filter requests.csv
benson: 003
  02 favicon.ico
  01 stats.html
rigby: 001
  01 favicon.ico
mordecai: 002
  02 stats.html
$ 
```

As shown, the program should require a single command line argument that is the `.csv` file to open in the current working directory.

So, in general:

```
host: <total>
  <count> file.ext
  <count> file.ext
  <count> file.ext
```

### Tips

A hash table would be quite useful for this...

### Makefile

Write a `Makefile` so that running `make` will compile a binary named `filter`.
