const m = 7, n = 85 /*符号缺失： ';'*/
var x, y, z, q r; /*符号缺失： ','*/
const ; /*后继缺失：const后缺少ident*/

procedure ; /*后继缺失：procedure后缺少ident*/
var a, b;
begin
	a := x; b := y; z := 0;
	while b > 0 do
	begin
		if odd b then z := (z + a * 1; /*匹配错误：括号*/
		a := 2 * a; b := b / 2;
	end;
end;

procedure gcd;
var ; /*后继缺失：var后缺少ident*/
begin
	f x; /*后继缺失：ident后缺少:=*/
	g := y;
	while f != g /*匹配错误：while do*/
	begin
		if f < g  g := g - f; /*匹配错误：if then*/
		if g < f then f := f - g;
end; /*匹配错误：begin end*/

begin
	x := m; y := n; call multiply;
	x := 34; y := 36; call gcd;
end /*符号缺失 '.'*/
