import datetime
import hashlib

data="ChenHao"

starttime = datetime.datetime.now()
print starttime
n=1
while n < 2**32:
    str = data + `n`
    hash = hashlib.sha256(str).hexdigest()
    hash = hashlib.sha256(hash).hexdigest()
    if hash.startswith('00000'):
        print  str, hash
        break
    n = n + 1

endtime = datetime.datetime.now()
print endtime
print "elapse: %d seconds!!!" % (endtime - starttime).seconds
