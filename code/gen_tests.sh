#!/usr/bin/env bash

# Create test directories
mkdir -p tests/{case01_generic_pal_and_match,case02_generic_common_block,case03_generic_empty_vs_nonempty,edge01_even_vs_odd_pal,edge02_no_common_substr,edge03_multi_hits_overlap}

# ---------- case01_generic_pal_and_match ----------
cat > tests/case01_generic_pal_and_match/transmission1.txt <<'EOF'
abcdeffedcxyz
EOF
cat > tests/case01_generic_pal_and_match/transmission2.txt <<'EOF'
ooodeffedooo
EOF
cat > tests/case01_generic_pal_and_match/mcode1.txt <<'EOF'
cde
EOF
cat > tests/case01_generic_pal_and_match/mcode2.txt <<'EOF'
ff
EOF
cat > tests/case01_generic_pal_and_match/mcode3.txt <<'EOF'
zzz
EOF
cat > tests/case01_generic_pal_and_match/expected.txt <<'EOF'
Test transmission 1
MCODE 1: true 3
MCODE 2: true 6
MCODE 3: false
Longest palindromic substring
3 10
Comparison between transmissions 1 and 2
4 9
Test transmission 2
MCODE 1: false
MCODE 2: true 6
MCODE 3: false
Longest palindromic substring
1 12
EOF

# ---------- case02_generic_common_block ----------
cat > tests/case02_generic_common_block/transmission1.txt <<'EOF'
racecar42
EOF
cat > tests/case02_generic_common_block/transmission2.txt <<'EOF'
xxracecarxx
EOF
cat > tests/case02_generic_common_block/mcode1.txt <<'EOF'
race
EOF
cat > tests/case02_generic_common_block/mcode2.txt <<'EOF'
car4
EOF
cat > tests/case02_generic_common_block/mcode3.txt <<'EOF'
zz
EOF
cat > tests/case02_generic_common_block/expected.txt <<'EOF'
Test transmission 1
MCODE 1: true 1
MCODE 2: true 5
MCODE 3: false
Longest palindromic substring
1 7
Comparison between transmissions 1 and 2
1 7
Test transmission 2
MCODE 1: true 3
MCODE 2: false
MCODE 3: false
Longest palindromic substring
1 11
EOF

# ---------- case03_generic_empty_vs_nonempty ----------
cat > tests/case03_generic_empty_vs_nonempty/transmission1.txt <<'EOF'
EOF
cat > tests/case03_generic_empty_vs_nonempty/transmission2.txt <<'EOF'
abc
EOF
cat > tests/case03_generic_empty_vs_nonempty/mcode1.txt <<'EOF'
a
EOF
cat > tests/case03_generic_empty_vs_nonempty/mcode2.txt <<'EOF'
bc
EOF
cat > tests/case03_generic_empty_vs_nonempty/mcode3.txt <<'EOF'
z
EOF
cat > tests/case03_generic_empty_vs_nonempty/expected.txt <<'EOF'
Test transmission 1
MCODE 1: false
MCODE 2: false
MCODE 3: false
Longest palindromic substring
No palindromic substring
Comparison between transmissions 1 and 2
No common substring
Test transmission 2
MCODE 1: true 1
MCODE 2: true 2
MCODE 3: false
Longest palindromic substring
1 1
EOF

# ---------- edge01_even_vs_odd_pal ----------
cat > tests/edge01_even_vs_odd_pal/transmission1.txt <<'EOF'
abccbaHELLO
EOF
cat > tests/edge01_even_vs_odd_pal/transmission2.txt <<'EOF'
xyzabccbaxyz
EOF
cat > tests/edge01_even_vs_odd_pal/mcode1.txt <<'EOF'
cc
EOF
cat > tests/edge01_even_vs_odd_pal/mcode2.txt <<'EOF'
HEL
EOF
cat > tests/edge01_even_vs_odd_pal/mcode3.txt <<'EOF'
cab
EOF
cat > tests/edge01_even_vs_odd_pal/expected.txt <<'EOF'
Test transmission 1
MCODE 1: true 3
MCODE 2: true 7
MCODE 3: false
Longest palindromic substring
1 6
Comparison between transmissions 1 and 2
1 6
Test transmission 2
MCODE 1: true 5
MCODE 2: false
MCODE 3: false
Longest palindromic substring
4 9
EOF

# ---------- edge02_no_common_substr ----------
cat > tests/edge02_no_common_substr/transmission1.txt <<'EOF'
aaaaaa
EOF
cat > tests/edge02_no_common_substr/transmission2.txt <<'EOF'
bbbbbb
EOF
cat > tests/edge02_no_common_substr/mcode1.txt <<'EOF'
aa
EOF
cat > tests/edge02_no_common_substr/mcode2.txt <<'EOF'
bbb
EOF
cat > tests/edge02_no_common_substr/mcode3.txt <<'EOF'
ab
EOF
cat > tests/edge02_no_common_substr/expected.txt <<'EOF'
Test transmission 1
MCODE 1: true 1
MCODE 2: false
MCODE 3: false
Longest palindromic substring
1 6
Comparison between transmissions 1 and 2
No common substring
Test transmission 2
MCODE 1: false
MCODE 2: true 1
MCODE 3: false
Longest palindromic substring
1 6
EOF

# ---------- edge03_multi_hits_overlap ----------
cat > tests/edge03_multi_hits_overlap/transmission1.txt <<'EOF'
aaaaa
EOF
cat > tests/edge03_multi_hits_overlap/transmission2.txt <<'EOF'
aaabaa
EOF
cat > tests/edge03_multi_hits_overlap/mcode1.txt <<'EOF'
aaa
EOF
cat > tests/edge03_multi_hits_overlap/mcode2.txt <<'EOF'
aa
EOF
cat > tests/edge03_multi_hits_overlap/mcode3.txt <<'EOF'
aab
EOF
cat > tests/edge03_multi_hits_overlap/expected.txt <<'EOF'
Test transmission 1
MCODE 1: true 1
MCODE 2: true 1
MCODE 3: false
Longest palindromic substring
1 5
Comparison between transmissions 1 and 2
1 3
Test transmission 2
MCODE 1: true 1
MCODE 2: true 1
MCODE 3: true 2
Longest palindromic substring
2 6
EOF
