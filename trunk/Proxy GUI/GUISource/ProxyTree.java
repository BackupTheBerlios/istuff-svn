import java.util.Iterator;
import java.util.ListIterator;

public class ProxyTree {

	private ProxyNode treeRoot;

	private ProxyNode currentNode;

	public ProxyTree() {
		treeRoot = new ProxyNode("RootProxy", "EH Proxies", "Virtual", "");
	}

	public void insertNode(ProxyNode node) {
		// Insert alphabetically
		ProxyNode predecessorNode;
		predecessorNode = searchPredecessorNode(treeRoot, node);
		if (predecessorNode != null)
			predecessorNode.addSuccessor(node);
	}

	private ProxyNode searchPredecessorNode(ProxyNode startNode,
			ProxyNode searchNode) {
		for (Iterator<ProxyNode> i = startNode.getSuccessors().iterator(); i
				.hasNext();) {
			ProxyNode compareKindNode = (ProxyNode) i.next();
			// check if kind is already there
			if (compareKindNode.getKind().equals(searchNode.getKind())) {
				// If the kind already exists, check wether the proxy class
				// already exists
				for (ListIterator<ProxyNode> it = compareKindNode
						.getSuccessors().listIterator(); it.hasNext();) {
					ProxyNode compareProxyClassNode = it.next();
					if (compareProxyClassNode.getproxyClass().equals(
							searchNode.getproxyClass())) {
						// Now also check if a node with the same FilePath
						// or is name better???
						// is already in the tree
						// ProxyNode compareProxy;
						for (Iterator<ProxyNode> proxyIterator = compareProxyClassNode
								.getSuccessors().iterator(); proxyIterator
								.hasNext();) {
							ProxyNode compareProxy = proxyIterator.next();
							if (compareProxy.getPathToFile().equals(
									searchNode.getPathToFile())) {
								// This means that the same node is already in
								// the tree
								return null;
							}

						}
						return compareProxyClassNode;
						// if the node does not exist in the tree, return the
						// ProxyClassNode
						// there the new node should be inserted
						// return compareKindNode;
					}

				}
				// No ProxyClass found --> Create a new one

				// Return the ProxyClassNode and insert the new node

				ProxyNode newProxyClassNode = new ProxyNode(searchNode
						.getKind(), searchNode.getproxyClass(), searchNode
						.getproxyClass(), "");
				// if the ProxyClass does not exist yet, create it
				// and return the newly created node
				compareKindNode.addSuccessor(newProxyClassNode);
				return newProxyClassNode;
			}

		}
		// In the case that the kind does not exist,
		// create new kind and proxyclass
		ProxyNode newKindNode = new ProxyNode(searchNode.getKind(), searchNode
				.getKind(), searchNode.getKind(), "");
		startNode.addSuccessor(newKindNode);
		// Now a new proxClass needs to be created as well
		// This can directly be done because the new node has no successors
		ProxyNode newProxyClassNode = new ProxyNode(searchNode.getKind(),
				searchNode.getproxyClass(), searchNode.getproxyClass(), "");
		newKindNode.addSuccessor(newProxyClassNode);
		return newProxyClassNode;
	}

	public boolean isInTree(ProxyNode searchNode) {
		for (Iterator<ProxyNode> kindIterator = getTreeRoot().getSuccessors()
				.iterator(); kindIterator.hasNext();) {
			ProxyNode compareKindNode = (ProxyNode) kindIterator.next();
			// check if kind is already there
			if (compareKindNode.getKind().equals(searchNode.getKind()))
				return (true);
			// If the node as kind does not exists, check wether the
			// node is a proxy class
			for (Iterator<ProxyNode> pClassIterator = compareKindNode
					.getSuccessors().iterator(); pClassIterator.hasNext();) {
				ProxyNode compareProxyClassNode = (ProxyNode) pClassIterator
						.next();
				if (compareProxyClassNode.getproxyClass().equals(
						searchNode.getproxyClass()))
					return (true);
				for (Iterator<ProxyNode> proxyIterator = compareKindNode
						.getSuccessors().iterator(); proxyIterator.hasNext();) {
					ProxyNode compareProxyNode = (ProxyNode) proxyIterator
							.next();
					if (compareProxyNode.getName().equals(searchNode.getName()))
						;
					return (true);
				}
			}
		}
		return false;
	}

	public ProxyNode getTreeRoot() {
		return treeRoot;
	}

	public ProxyNode getCurrentNode() {
		return currentNode;
	}
}