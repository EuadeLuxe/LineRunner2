/*
 * cfgFile
 * author: Marvin Blum
 * last update: 2014/04/23 13:17
 *
 * Reads and writes cfg files.
 */

#ifndef CFGFILE_H_
#define CFGFILE_H_

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <fstream>

namespace bb{

class cfgFile{
	public:
		class Node{
			friend cfgFile;

			public:
				enum class TYPE{
					STRING,
					INT,
					FLOAT,
					CLASS
				};

			private:
				TYPE type;
				std::string name;
				std::list<std::shared_ptr<Node>> children;

				Node(const std::string &name, const std::string &value, const TYPE type);

				std::shared_ptr<Node> set(const std::string &name, const std::string &value, const TYPE type); // or add if not exists

			public:
				std::vector<std::string> value;

				Node(const std::string &name, const std::string &value);
				Node(const std::string &name, const int value);
				Node(const std::string &name, const float value);
				Node(const std::string &name);

				std::shared_ptr<Node> set(const std::string &name, const std::string &value);
				std::shared_ptr<Node> set(const std::string &name, const int value);
				std::shared_ptr<Node> set(const std::string &name, const float value);
				std::shared_ptr<Node> set(const std::string &name);
				void set(const std::shared_ptr<Node> node);

				bool remove(const std::string &name);
				void removeAll(const std::string &name);
				void remove(const std::shared_ptr<Node> node);

				TYPE getType();
				const std::string& getName();

				std::shared_ptr<Node> get(const std::string &name); // or "find" (not recursively!)
				void getClasses(const std::string &name, std::list<std::shared_ptr<Node>> &list);
				const std::list<std::shared_ptr<Node>>& getChildren();

				std::string toString(const unsigned int i = 0);
				int toInt(const unsigned int i = 0);
				float toFloat(const unsigned int i = 0);
		};

	private:
		std::shared_ptr<Node> root;

		// these are help functions
		void write(std::ofstream &file, std::shared_ptr<Node> node, std::string tabs = "");
		std::string escape(const std::string &value);
		Node::TYPE testType(const std::string &value);

	public:
		cfgFile();

		bool read(const std::string &path);
		bool write(const std::string &path, const bool addComment = true);

		std::shared_ptr<Node> getRoot();
};

};

#endif
