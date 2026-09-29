#include "LexicalTree.h"

LexicalTree::LexicalTree(const std::string & er) : _er(er), allid(0) {
	Node * tag = new Node(NodeT::VALUE);
	tag->value = "#";
	root = new Node(NodeT::CAT);
	root->r = tag;

	generate_tree();
}

void LexicalTree::generate_tree() {
	std::string er(_er.rbegin(), _er.rend());

	root->l = generate_subtree(er);
}

Node * LexicalTree::generate_subtree(std::string & er) {
	if (er.empty()) return nullptr;
	if (er.size() == 1) {
		Node * n = new Node(NodeT::VALUE);
		n->value = er[0];
		return n;
	}

	// Procurar OU fora do () e []
	// Procurar CAT fora do () e []
	// *, + e ?
	// TODO: Falta apenas grupos como [a-zA-Z], [0-9]
	size_t f_p  = er.find(")");
	size_t f_p2 = er.find("(");
	size_t f_c  = er.find("]");
	size_t f_c2 = er.find("[");
	size_t f_or = er.find("|");

	if (((f_or < f_p && f_or < f_p2) || (f_or > f_p && f_or > f_p2)) 
	&&  ((f_or < f_c && f_or < f_c2) || (f_or > f_c && f_or > f_c2))) {
		Node * n = new Node(NodeT::OR);
		n->l = generate_subtree(...) // Passar ER sliced para subtree
		n->r = generate_subtree(...)

		return un;
	}

	size_t ix = find_valid_value(er);

	if (ix != std::string::npos && ((ix < f_p && ix < f_p2) || (ix > f_p && ix > f_p2))) {
		Node * n = new Node(NodeT::CAT);
		n->r = generate_subtree(...) // Passar ER[:ix];
		n->l = generate_subtree(...) // Passar ER[ix:];
		return n;
	}

	char cur = er[0];
	if (cur == "*") {
		Node * n = new Node(NodeT::STAR);
		n->l = generate_subtree(...) // Passar ER a partir do *, agora ou é um elemento ou 
		return n;
	}
	if (cur == "+") {
		Node * n = new Node(NodeT::CROSS);
		n->l = generate_subtree(...) // Passar ER a partir do +, agora ou é um elemento ou 
			return n;

	}
	if (cur == "?") {
		Node * n = new Node(NodeT::OPT);
		n->l = generate_subtree(...) // Passar ER a partir do ?, agora ou é um elemento ou 
			return n;
	}
}

size_t LexicalTree::find_valid_value(std::string & er) {
	// FIND TO CONCATENATE, return -1
	size_t p, p2, c;
	bool open = false;
	char open_t = '';
	int st = 0;
	std::string symbols = "()[]*+?|";
	for (size_t i = 0; i < er.size(); i++) {
		if (symbols.find(er[i]) == std::string::npos && !open) return i;
		if (er[i] == ')' && !open) {
			if (st == 0) {
				open = true;
				open_t = '(';
			}
			if (open_t == '(') st++;
		}
		else if (er[i] == '(') {
			if (open_t == er[i])
				if (--st == 0) return i;
		}
		else if (er[i] == ']' && !open) {
			if (st == 0) {
				open = true;
				open_t = '[';
			}
			if (open_t == '[') st++;
		}
		else if (er[i] == '[') {
			if (open_t == er[i])
				if (--st == 0) return i;
		}
	}

	return -1;
}
