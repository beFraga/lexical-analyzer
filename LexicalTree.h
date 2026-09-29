#include <string>

enum class NodeT { CAT, OR, VALUE, STAR, OPT, CROSS };

class LexicalTree {
public:
	struct Node {
		int id;
		NodeT type;
		Node * l;
		Node * r;
		std::string value;
		// Conjuntos first, last, follow (Usar algoritmo de Conjuntos)

		Node(NodeT type) : id(allid++), type(type), l(nullptr), r(nullptr);
	}
	
	LexicalTree(const std::string & er);

	void generate_tree();
	Node * generate_subtree(std::string & er);

	size_t find_valid_value(std::string & er);

	void tree_first();
	void tree_last();
	void tree_follow();

	void calc_first(Node &* node);
	void calc_last(Node &* node);
	void calc_follow(Node &* node);

private:
	const std::string _er;
	Node * root;
	int allid;
}
