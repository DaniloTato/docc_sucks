#!/usr/bin/env bash

# Create test directories
mkdir -p tests/{case01_basic_example,case02_single_item_fits,case03_single_item_no_fit,case04_all_items_fit,case05_zero_capacity,case06_no_items,case07_same_weights,case08_larger_example}

# ---------- case01_basic_example ----------
cat > tests/case01_basic_example/input.txt <<'EOF'
4
60 100 120 80
10 20 30 15
50
EOF
cat > tests/case01_basic_example/expected.txt <<'EOF'
240
EOF

# ---------- case02_single_item_fits ----------
cat > tests/case02_single_item_fits/input.txt <<'EOF'
1
100
10
20
EOF
cat > tests/case02_single_item_fits/expected.txt <<'EOF'
100
EOF

# ---------- case03_single_item_no_fit ----------
cat > tests/case03_single_item_no_fit/input.txt <<'EOF'
1
100
30
20
EOF
cat > tests/case03_single_item_no_fit/expected.txt <<'EOF'
0
EOF

# ---------- case04_all_items_fit ----------
cat > tests/case04_all_items_fit/input.txt <<'EOF'
3
10 20 30
1 2 3
10
EOF
cat > tests/case04_all_items_fit/expected.txt <<'EOF'
60
EOF

# ---------- case05_zero_capacity ----------
cat > tests/case05_zero_capacity/input.txt <<'EOF'
3
10 20 30
1 2 3
0
EOF
cat > tests/case05_zero_capacity/expected.txt <<'EOF'
0
EOF

# ---------- case06_no_items ----------
cat > tests/case06_no_items/input.txt <<'EOF'
0


50
EOF
cat > tests/case06_no_items/expected.txt <<'EOF'
0
EOF

# ---------- case07_same_weights ----------
cat > tests/case07_same_weights/input.txt <<'EOF'
2
50 100
10 10
10
EOF
cat > tests/case07_same_weights/expected.txt <<'EOF'
100
EOF

# ---------- case08_larger_example ----------
cat > tests/case08_larger_example/input.txt <<'EOF'
5
10 40 30 50 35
5 4 6 3 2
10
EOF
cat > tests/case08_larger_example/expected.txt <<'EOF'
125
EOF
