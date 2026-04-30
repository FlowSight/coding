You’re	given	an	array	of	CSV	strings	representing	search	results.	Results	are	sorted	by	a	score	initially.	A	
given	host	may	have	several	listings	that	show	up	in	these	results.	Suppose	we	want	to	show	12	results	
per	page,	but	we	don’t	want	the	same	host	to	dominate	the	results.	Write	a	function	that	will	reorder	
the	list	so	that	a	host	shows	up	at	most	once	on	a	page	if	possible,	but	otherwise	preserves	the	ordering.	
Your	program	should	return	the	new	array	and	print	out	the	results	in	blocks	representing	the	pages.	
Input: An	array	of	csv	strings,	with	sort	score	number	of	results	per	page.	example:	

"host_id,listing_id,score,city"

5
13
1,28,310.6,SF	
4,5,204.1,SF	
20,7,203.2,Oakland	
6,8,202.2,SF
6,10,199.1,SF	
1,16,190.4,SF	
6,29,185.2,SF	
7,20,180.1,SF	
6,21,162.1,SF
2,18,161.2,SF	
2,30,149.1,SF
3,76,146.2,SF	
2,14,141.1,San	Jose

output:
1,28,310.6,SF
4,5,204.1,SF
20,7,203.2,Oakland
6,8,202.2,SF	
7,20,180.1,SF	


6,10,199.1,SF	
1,16,190.4,SF	
2,18,161.2,SF
3,76,146.2,SF	
6,29,185.2,SF 

6,21,162.1,SF
2,30,149.1,SF
2,14,141.1,San	Jose


