#!/usr/bin/python2
#vim: set fileencoding=utf-8 :
import sys
import matplotlib.pyplot as plt
import networkx as nx

filename = sys.argv[1]
f = open(filename, 'rU')
degreeList = [int(x) for x in f.readline().split(' ')]
treeSize = len(degreeList)

###############
# Checking    #
###############
if treeSize <= 0:
	print u'Ошибка: Неположительный размер дерева!'
	sys.exit(1)

for degree in degreeList:
	if degree < 1:
		print u'Ошибка: Есть вершины со степенью меньшей 1!'
		sys.exit(1)

degreeSum = sum(degreeList)
if degreeSum != (treeSize - 1) * 2:
	print u'Ошибка: Сумма степеней вершин не соотвествует тому, что граф дерево!'
	sys.exit(1)

###############
# Main logic  #
###############
cutDegreeList = [x - 1 for x in degreeList]

def constructNxGraph(tree):
	global degreeList

	graph = nx.Graph()
	for node in tree.keys():
		for relatedNode in tree[node]:
			graph.add_edge(
				str(node) + ' ' + str(degreeList[node])
				, str(relatedNode) + ' ' + str(degreeList[relatedNode])
				)
	return graph

count = 0
def constructTrees(degreeList, curDegList=[], pos=0):
	global count

	if pos == len(degreeList):
		generatedList = generateTree(curDegList)

		if generatedList:
			for tree in generatedList:
				count += 1
				nxgraph = constructNxGraph(tree)
				nx.draw(nxgraph)
				# plt.savefig('ex' + str(count) + '.png')
				plt.show()
		return

	if (degreeList[pos] == 1):
		constructTrees(degreeList, curDegList + [0], pos + 1)
		return

	for i in xrange(1, degreeList[pos] + 1):
		constructTrees(degreeList, curDegList + [i], pos + 1)

# Возвращает list of {(vertexNum, [list of connected verteces])}
def generateTree(curDegList):
	i = 0
	structVertexDegDict = {}
	for deg in curDegList:
		if deg != 0:
			structVertexDegDict[i] = deg
		i += 1

	#tree check
	degSum = sum(structVertexDegDict.values())
	if (degSum != 2 * (len(structVertexDegDict) - 1)):
		return []

	constructor = TreeConstructor(structVertexDegDict)
	return constructor.constructTreeList()

class TreeConstructor:
	def __init__(self, structVertexDegDict):
		self.structVertexDegDict = structVertexDegDict
		
		self.currentDegreeDecriment = {}
		for vert in structVertexDegDict:
			self.currentDegreeDecriment[vert] = 0

	def constructTreeList(self):
		minVertex = min(self.structVertexDegDict.keys())
		reviewList = [(minVertex, self.structVertexDegDict[minVertex])]		
		unusedVertices = set(self.structVertexDegDict.keys())
		unusedVertices.remove(minVertex)

		result = self.__treeByReviewList(1, reviewList, unusedVertices, set()) 
		return result


	def __treeByReviewList(self, number, reviewList, unusedVertices, alreadyObserved, treeDict1 = {}):
		treeDict = treeDict1.copy()

		# print 'AAA', number, 'HHH', reviewList, unusedVertices, alreadyObserved, treeDict
		if not reviewList and not unusedVertices:
			return [treeDict]

		if not reviewList:
			return []

		curVertex, curDegree = reviewList[0]
		if curDegree == 0:
			return self.__treeByReviewList(2 * number, reviewList[1:], unusedVertices | alreadyObserved, set(), treeDict)

		if reviewList and not unusedVertices:
			return []

		observingVertex = iter(unusedVertices).next()

		appendTreeDict = {}
		for elem in treeDict.keys():
			appendTreeDict[elem] = treeDict[elem].copy()

		if curVertex not in appendTreeDict:
			appendTreeDict[curVertex] = set()
		appendTreeDict[curVertex].add(observingVertex)

		print '\t', treeDict
		print '\t', appendTreeDict
		print '\t', treeDict == appendTreeDict


		secondResult = self.__treeByReviewList(
			2 * number + 1
			, reviewList
			, unusedVertices - set([observingVertex])
			, alreadyObserved | set([observingVertex])
			, treeDict
			)

		if curVertex not in appendTreeDict:
			appendTreeDict[curVertex] = set()
		appendTreeDict[curVertex].add(observingVertex)

		print '\t', treeDict
		print '\t', appendTreeDict

		firstResult = self.__treeByReviewList(
			2 * number
			, [(curVertex, curDegree - 1)] + reviewList[1:] + [(observingVertex, self.structVertexDegDict[observingVertex] - 1)]
			, unusedVertices - set([observingVertex])
			, alreadyObserved
			, appendTreeDict
			)

		return firstResult + secondResult

###############
# Main phase  #
###############
constructTrees(degreeList)

print count