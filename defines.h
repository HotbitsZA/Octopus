#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#define HOME 0
#define DRAW 1
#define AWAY 2

#define SPAIN   0
#define ITALY   1
#define ENGLAND 2
#define GERMANY 3

//PSL teams
#define AMAZULU		0
#define ARROWS		1
#define BAROKA		2
#define CELTIC		3
#define CHIEFS		4
#define CHIPPA		5
#define CPTC		6
#define HPARK		7
#define LEOPARDS	8
#define MARITZBURG	9
#define PIRATES		10
#define PLKCITY		11
#define SSU			12
#define STELLENBOSCH	13
#define SUNDOWNS	14
#define WITS		15
//Bundeliga teams
#define AUGSBURG 		0
#define BAYERNM 		1
#define DORTMUND 		2
#define DUSSELDORF 		3
#define FCKOLN 			4
#define FRANKFURT 		5
#define FREIBURG 		6
#define HERTHABERLIN 	7
#define HOFFENHEIM 		8
#define LEIPZIG 		9
#define LEVERKUSEN 		10
#define MAINZ 			11
#define MONCHENGLADBACH	12
#define PADERBORN 		13
#define SCHALKE 		14
#define UNIONBERLIN 	15
#define WERDER 			16
#define WOLFS 			17
//EPL
#define ARSENAL		0
#define AVILLA 		1
#define BHA 		2
#define BOURNEMOUTH 3
#define BURNELY 	4
#define CHELSEA 	5
#define CPALACE 	6
#define EVERTON 	7
#define LEICESTER 	8
#define LIVERPOOL 	9
#define MANCITY 	10
#define MANUTD 		11
#define NEWCASTLE 	12
#define NORWICH 	13
#define SHEFFIELD 	14
#define SOUTHAMPTON 15
#define TOTTENHAM 	16
#define WATFORD 	17
#define WHUTD 		18
#define WOLVES 		19
//LaLiga
#define ABILBAO     0
#define ALAVES      1
#define AMADRID     2
#define BARCELONA   3
#define CELTA       4
#define EIBAR       5
#define ESPANYOL    6
#define GETAFE      7
#define GRANADA     8
#define LEGANES     9
#define LEVANTE     10
#define MALLORCA    11
#define OSASUNA     12
#define RBETIS      13
#define RMADRID     14
#define RSOCIEDAD   15
#define RVALLADOLID 16
#define SEVILLA     17
#define VALENCIA    18
#define VILLAREAL   19
//Serie A
#define ACMILAN     0
#define ATALANTA    1
#define BOLOGNA     2
#define BRESCIA     3
#define CAGLIARI    4
#define FIORENTINA  5
#define GENOA       6
#define INTER       7
#define JUVENTUS    8
#define LAZIO       9
#define LECCE       10
#define NAPOLI      11
#define PARMA       12
#define ROMA        13
#define SAMPDORIA   14
#define SASSUOLO    15
#define SPAL        16
#define TORINO      17
#define UDINESE     18
#define VERONA      19

enum {TEN=0, TWENTY, THIRTY, FOURTY, FIFTY, SIXTY, SEVENTY, EIGHTY, NINETY, HUNDRED};
typedef std::vector<std::pair<double, double>> AllowedRange;
struct AllowedRanges
{
    AllowedRange home;
    AllowedRange draw;
    AllowedRange away;
};

#endif // DEFINES_H_INCLUDED
