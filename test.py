import sys

def test(pOut, pFix, pIn):
	nn = int(pOut[0])
	if nn<pFix:
		print("wrong value")
		return
	pendrvMax = pIn[0][1]
	if pOut[1]!="1:":
		print("invalid output format")
		return
	sVal = {}
	for i in range(1, len(pIn)):
		sVal[pIn[i][0]] = pIn[i][1]
	i = 2
	prevVal,pendrv = 4000000000, pendrvMax
	usedId = set()
	while i<len(pOut):
		if pOut[i]=="2:": 
			i+=1
			break
		val = int(pOut[i])
		if prevVal<val:
			print("incorrect order")
			return
		prevVal = val
		if val not in sVal:
			print("unknown id")
			return
		pendrv -= sVal[val]
		if pendrv<0:
			print("pendrive out of space")
			return
		if val in usedId:
			print("id used twice")
			return
		usedId.add(val)
		i+=1
		
	prevVal,pendrv = 4000000000, pendrvMax
	while i<len(pOut):
		val = int(pOut[i])
		if prevVal<val:
			print("incorrect order")
			return
		prevVal = val
		if val not in sVal:
			print("unknown id")
			return
		pendrv -= sVal[val]
		if pendrv<0:
			print("pendrive out of space")
			return
		if val in usedId:
			print("id used twice")
			return
		usedId.add(val)
		i+=1

	if len(usedId)!=nn:
		print("invalid list length")
		return
	print("OK")

def testPlik(nPlikOut, nPlikOutFix, nPlikIn):
	pOut=[]
	pFix=0
	pIn=[]
	tp1, tp2, tp3 = False, False, False
	with open(nPlikOut) as f:
		ll = list(f.readlines())
		ll = ' '.join( ll )
		pOut = ll.split()
		tp1 = True
	if not tp1: 
		print("File %s is not available"%(nPlikOut,))
		return
	with open(nPlikOutFix) as f:
		ll = f.readline()
		ll.split()
		pFix = int(ll[0])
		tp2 = True
	if not tp2:
		print("File %s is not available"%(nPlikOutFix,))
		return
	with open(nPlikIn) as f:
		ll = f.readline()
		ll = ll.split()
		pIn.append((int(ll[0]), int(ll[1])))
		for ll in f.readlines():
			ll = ll.split()
			pIn.append((int(ll[0]), int(ll[1])))
		tp3 = True
	if not tp3:
		print("File %s is not available"%(nPlikIn,))
		return
		
	test(pOut, pFix, pIn)
		
		
if __name__=="__main__":
	if len(sys.argv)!=4:
		print("test outputFile outputExampleFile inputFile")
	else:
		testPlik(sys.argv[1], sys.argv[2], sys.argv[3])