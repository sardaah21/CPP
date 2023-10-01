template<typename Node, typename Update>
struct SegTree_2D {
	vector<vector<Node>> tree;
    vector<vector<ll>> arr; //type may change
	int n,m; // n x m matrix
	int s,t;

    SegTree_2D(vector<vector<ll>> &a) { // change if type updated
		arr = a;
		n = a.size();
        m = a[0].size();
		s = 1;
		while(s < 2 * n){
			s = s << 1;
		}
        t = 1;
		while(t < 2 * m){
			t = t << 1;
		}

		tree.resize(s,vector<Node>(t)); // may change
		build();
	}
    
    /*---------------------------------<Build Section>---------------------------------*/
    void build_y(int vx, int lx, int rx, int vy, int ly, int ry) { // Never change this
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = Node(arr[lx][ly]);
            else
                tree[vx][vy].merge( tree[vx*2+1][vy], tree[vx*2+2][vy]);
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2+1, ly, my);
            build_y(vx, lx, rx, vy*2+2, my+1, ry);
            tree[vx][vy].merge(tree[vx][vy*2+1] , tree[vx][vy*2+2]);
        }
    }
    void build_x(int vx, int lx, int rx) { // Never change this
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx*2+1, lx, mx);
            build_x(vx*2+2, mx+1, rx);
        }
        build_y(vx, lx, rx, 0, 0, m-1);
    }
	void build(){  // Never change this
		build_x(0,0,n-1);
	}
    /*---------------------------------</Build Section>---------------------------------*/
    /*---------------------------------<Querey Section>---------------------------------*/
    Node sum_y(int vx, int vy, int tly, int try_, int ly, int ry) { //Never change this
        if (ly > ry){ 
            Node Identity;
            return Identity;
        }
        if (ly == tly && try_ == ry)
            return tree[vx][vy];
        int tmy = (tly + try_) / 2;
        Node ans,l,r;
        l=sum_y(vx, vy*2+1, tly, tmy, ly, min(ry, tmy));
        r=sum_y(vx, vy*2+2, tmy+1, try_, max(ly, tmy+1), ry);
        ans.merge(l,r);
        return ans;
    }
    Node sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry){ //Never change this
        if (lx > rx){
            Node Identity;
            return Identity;
        }
        if (lx == tlx && trx == rx)
            return sum_y(vx, 0, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        Node ans,l,r;
        l=sum_x(vx*2+1, tlx, tmx, lx, min(rx, tmx), ly, ry);
        r=sum_x(vx*2+2, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
        ans.merge(l,r);
        return ans;
    }
    Node make_query(int lx, int rx,int ly,int ry) { //Never change this
		Node ans;
        ans=sum_x(0,0,n-1,lx,rx,ly,ry);
        return ans;
	}
    /*---------------------------------</Querey Section>---------------------------------*/

    /*---------------------------------<Update Section>---------------------------------*/
    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, Update& new_val) {
        if (ly == ry) {
            if (lx == rx)
                new_val.apply(tree[vx][vy]);
            else
                tree[vx][vy].merge(tree[vx*2+1][vy] , tree[vx*2+2][vy]);
        } else {
            int my = (ly + ry) / 2;
            if (y <= my)
                update_y(vx, lx, rx, vy*2+1, ly, my, x, y, new_val);
            else
                update_y(vx, lx, rx, vy*2+2, my+1, ry, x, y, new_val);
            tree[vx][vy].merge(tree[vx][vy*2+1] , tree[vx][vy*2+2]);
        }
    }
    void update_x(int vx, int lx, int rx, int x, int y, Update& new_val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                update_x(vx*2+1, lx, mx, x, y, new_val);
            else
                update_x(vx*2+2, mx+1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 0, 0, m-1, x, y, new_val);
    }

	void make_update(int i,int j, ll val) {  // pass in as many parameters as required
		Update new_val = Update(val); // may change
		update_x(0,0, n - 1, i,j, new_val);
	}
    /*---------------------------------</Update Section>---------------------------------*/
};

struct Node1 {
	ll val; // may change
	Node1() { // Identity element
		val = (ll)0;	// may change
	}
	Node1(ll p1) {  // Actual Node
		val = p1; // may change
	}
	void merge(Node1 &l, Node1 &r) { // Merge two child nodes
		val = l.val + r.val;  // may change
	}
};

struct Update1 {
	ll val; // may change
	Update1(ll p1) { // Actual Update
		val = p1; // may change
	}
	void apply(Node1 &a) { // apply update to given node
		a.val = val; // may change
	}
};