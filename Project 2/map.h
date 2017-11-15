#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <utility>

namespace KW
{
	template<typename Key_Type, typename Value_Type>
	class Map {
	public:

		typedef std::pair<const Key_Type, Value_Type> Entry_Type;

		struct Key_Compare {
			bool operator()(const Entry_Type& left, const Entry_Type& right) const {
				return left.first < right.first;
			}
		};

		typedef typename std::set<Entry_Type, Key_Compare>::iterator iterator;

		typedef typename std::set<Entry_Type, Key_Compare>::const_iterator const_iterator;

		iterator begin(){
			return the_set.begin();
		}

		const_iterator begin() const{
			return the_set.begin();
		}

		iterator end() {
			return the_set.end();
		}

		const_iterator end() const {
			return the_set.end();
		}

		bool empty(){
			return the_set.empty();
		}

		int size(){
			return the_set.size();
		}

		std::pair<iterator, bool> insert(const Entry_Type& item){

			return the_set.insert(item);
		}

		void erase(const Key_Type& key){
			the_set.erase(Entry_Type(key, Value_Type()));
		}

		iterator find(const Key_Type& key){
			//return the_set.find(Entry_Type(key, Value_Type()));
			return the_set.find(Entry_Type(key, "ok"));
		}

		Value_Type& operator [](const Key_Type& key){
			std::pair<iterator, bool> ret = the_set.insert(Entry_Type(key, Value_Type()));
			Entry_Type& entry(const_cast<Entry_Type&>(*(ret.first)));
			return entry.second;
		}

	private:
		std::set<Entry_Type, Key_Compare> the_set;


	};


}

#endif