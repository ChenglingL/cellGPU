// Copyright (c) 2006-2008 Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/v5.5.2/Modular_arithmetic/include/CGAL/primes.h $
// $Id: primes.h 0779373 2020-03-26T13:31:46+01:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Michael Hemmer    <hemmer@mpi-inf.mpg.de>
//
// =============================================================================

#ifndef CGAL_PRIMES_H
#define CGAL_PRIMES_H

#include <CGAL/basic.h>

namespace CGAL {
namespace internal {

const int primes[2000] = {
  /*
  * Generated in SAGE with:
  *
  * N = 2000
  * p = 2^26
  * L = []
  * while len(L) < N:
  *   p = previous_prime(p)
  *   if GF(p)(2).is_primitive_root():
  *     L.append(p)
  * k = 8
  * for i in range(N/k):
  *   print '  ' + ', '.join (str(p) for p in L[k*i:k*(i+1)]) + ','
  */
  67108859, 67108819, 67108763, 67108757, 67108747, 67108739, 67108709, 67108693,
  67108669, 67108667, 67108661, 67108597, 67108579, 67108507, 67108493, 67108453,
  67108387, 67108373, 67108331, 67108219, 67108187, 67108109, 67108037, 67108003,
  67107941, 67107797, 67107787, 67107773, 67107757, 67107749, 67107707, 67107643,
  67107541, 67107539, 67107533, 67107461, 67107427, 67107389, 67107323, 67107317,
  67107301, 67107253, 67107203, 67107149, 67107043, 67106987, 67106821, 67106813,
  67106797, 67106749, 67106717, 67106693, 67106483, 67106477, 67106357, 67106339,
  67106323, 67106243, 67106213, 67106189, 67106107, 67106099, 67106093, 67106059,
  67105963, 67105933, 67105877, 67105867, 67105811, 67105771, 67105763, 67105699,
  67105691, 67105517, 67105459, 67105453, 67105373, 67105349, 67105267, 67105187,
  67105141, 67105133, 67105061, 67104997, 67104931, 67104923, 67104893, 67104883,
  67104859, 67104803, 67104757, 67104707, 67104691, 67104589, 67104581, 67104571,
  67104563, 67104539, 67104517, 67104437, 67104419, 67104379, 67104341, 67104293,
  67104277, 67104251, 67104227, 67104139, 67104061, 67104053, 67103963, 67103909,
  67103867, 67103851, 67103837, 67103821, 67103731, 67103669, 67103653, 67103587,
  67103579, 67103549, 67103507, 67103483, 67103219, 67103173, 67103149, 67103147,
  67103107, 67103083, 67103051, 67103027, 67103021, 67102963, 67102949, 67102901,
  67102843, 67102733, 67102627, 67102613, 67102531, 67102499, 67102459, 67102397,
  67102333, 67102331, 67102283, 67102237, 67102181, 67102163, 67102099, 67102093,
  67102069, 67102067, 67102019, 67101997, 67101989, 67101899, 67101883, 67101877,
  67101779, 67101739, 67101691, 67101637, 67101613, 67101509, 67101493, 67101491,
  67101469, 67101443, 67101413, 67101341, 67101323, 67101299, 67101187, 67101173,
  67101053, 67100987, 67100981, 67100963, 67100947, 67100939, 67100909, 67100899,
  67100861, 67100851, 67100827, 67100773, 67100731, 67100699, 67100669, 67100659,
  67100653, 67100587, 67100459, 67100357, 67100347, 67100179, 67100141, 67100123,
  67100101, 67099987, 67099957, 67099931, 67099861, 67099853, 67099829, 67099819,
  67099699, 67099589, 67099547, 67099541, 67099517, 67099499, 67099397, 67099387,
  67099363, 67099339, 67099267, 67099213, 67099141, 67099133, 67099037, 67098931,
  67098923, 67098917, 67098907, 67098827, 67098821, 67098739, 67098653, 67098589,
  67098419, 67098389, 67098347, 67098341, 67098323, 67098299, 67098277, 67098259,
  67098203, 67098197, 67098179, 67098149, 67098067, 67098029, 67097917, 67097819,
  67097813, 67097803, 67097747, 67097699, 67097669, 67097659, 67097579, 67097413,
  67097363, 67097339, 67097333, 67097291, 67097269, 67097123, 67097053, 67096987,
  67096979, 67096973, 67096907, 67096867, 67096837, 67096693, 67096669, 67096507,
  67096499, 67096483, 67096411, 67096387, 67096373, 67096301, 67096109, 67096067,
  67096021, 67096013, 67095989, 67095971, 67095893, 67095869, 67095797, 67095731,
  67095701, 67095683, 67095667, 67095659, 67095629, 67095499, 67095421, 67095419,
  67095349, 67095317, 67095173, 67095139, 67095131, 67095101, 67095037, 67095011,
  67094987, 67094981, 67094917, 67094899, 67094891, 67094837, 67094827, 67094723,
  67094717, 67094707, 67094701, 67094581, 67094557, 67094507, 67094501, 67094459,
  67094437, 67094411, 67094389, 67094309, 67094299, 67094267, 67094141, 67094123,
  67094099, 67093979, 67093933, 67093931, 67093861, 67093853, 67093757, 67093723,
  67093699, 67093627, 67093619, 67093613, 67093603, 67093597, 67093547, 67093349,
  67093307, 67093181, 67093171, 67093163, 67093157, 67093109, 67093069, 67093043,
  67093003, 67092997, 67092947, 67092869, 67092821, 67092787, 67092757, 67092749,
  67092709, 67092691, 67092643, 67092611, 67092563, 67092539, 67092491, 67092461,
  67092419, 67092331, 67092323, 67092301, 67092227, 67092203, 67092197, 67092107,
  67091987, 67091939, 67091933, 67091923, 67091797, 67091779, 67091771, 67091669,
  67091611, 67091491, 67091477, 67091443, 67091357, 67091341, 67091243, 67091203,
  67091149, 67091107, 67091029, 67090979, 67090973, 67090939, 67090861, 67090763,
  67090627, 67090613, 67090589, 67090579, 67090549, 67090547, 67090523, 67090459,
  67090451, 67090411, 67090403, 67090307, 67090259, 67090229, 67090189, 67090117,
  67090099, 67090091, 67090043, 67090027, 67090013, 67089949, 67089829, 67089739,
  67089733, 67089707, 67089683, 67089587, 67089541, 67089461, 67089299, 67089283,
  67089277, 67089221, 67089059, 67088963, 67088821, 67088797, 67088779, 67088717,
  67088683, 67088653, 67088627, 67088621, 67088603, 67088597, 67088573, 67088509,
  67088501, 67088453, 67088429, 67088381, 67088347, 67088267, 67088117, 67088093,
  67088059, 67087973, 67087957, 67087901, 67087883, 67087859, 67087723, 67087717,
  67087637, 67087571, 67087547, 67087459, 67087451, 67087421, 67087277, 67087259,
  67087243, 67087187, 67087123, 67087019, 67086949, 67086931, 67086917, 67086893,
  67086869, 67086827, 67086757, 67086667, 67086637, 67086629, 67086611, 67086589,
  67086421, 67086347, 67086323, 67086317, 67086307, 67086293, 67086259, 67086109,
  67086067, 67086053, 67086043, 67086013, 67085939, 67085933, 67085899, 67085869,
  67085867, 67085861, 67085819, 67085813, 67085803, 67085771, 67085741, 67085677,
  67085531, 67085443, 67085437, 67085429, 67085357, 67085341, 67085267, 67085189,
  67085173, 67085171, 67085099, 67085093, 67085003, 67084981, 67084973, 67084931,
  67084861, 67084789, 67084757, 67084709, 67084643, 67084637, 67084603, 67084547,
  67084517, 67084483, 67084427, 67084349, 67084333, 67084331, 67084309, 67084189,
  67084187, 67084139, 67084013, 67083883, 67083859, 67083811, 67083803, 67083787,
  67083739, 67083707, 67083629, 67083619, 67083613, 67083539, 67083517, 67083461,
  67083437, 67083371, 67083323, 67083221, 67083197, 67083067, 67082989, 67082987,
  67082963, 67082933, 67082909, 67082891, 67082861, 67082843, 67082779, 67082707,
  67082699, 67082579, 67082549, 67082531, 67082453, 67082363, 67082339, 67082227,
  67082189, 67082131, 67082123, 67082101, 67082003, 67081957, 67081829, 67081811,
  67081787, 67081741, 67081733, 67081709, 67081691, 67081661, 67081579, 67081499,
  67081477, 67081429, 67081283, 67081237, 67081213, 67081211, 67081139, 67081123,
  67081051, 67080971, 67080947, 67080917, 67080859, 67080821, 67080803, 67080763,
  67080701, 67080653, 67080557, 67080491, 67080437, 67080413, 67080323, 67080179,
  67080173, 67080131, 67080107, 67080061, 67079981, 67079963, 67079941, 67079933,
  67079917, 67079693, 67079587, 67079491, 67079459, 67079429, 67079347, 67079333,
  67079323, 67079317, 67079267, 67079237, 67079219, 67079213, 67079203, 67079149,
  67079141, 67079123, 67079083, 67079027, 67078981, 67078931, 67078877, 67078819,
  67078813, 67078789, 67078763, 67078643, 67078573, 67078469, 67078387, 67078331,
  67078309, 67078301, 67078283, 67078213, 67078181, 67078139, 67078133, 67078069,
  67078061, 67078013, 67077947, 67077917, 67077851, 67077827, 67077797, 67077757,
  67077643, 67077611, 67077541, 67077539, 67077419, 67077403, 67077379, 67077349,
  67077341, 67077299, 67077293, 67077259, 67077181, 67077173, 67077133, 67076899,
  67076869, 67076851, 67076843, 67076803, 67076773, 67076741, 67076693, 67076683,
  67076677, 67076651, 67076629, 67076627, 67076573, 67076539, 67076413, 67076411,
  67076357, 67076341, 67076291, 67076189, 67076147, 67076117, 67076077, 67076069,
  67076029, 67075973, 67075949, 67075933, 67075907, 67075867, 67075787, 67075691,
  67075669, 67075573, 67075493, 67075373, 67075363, 67075277, 67075243, 67075147,
  67075109, 67075091, 67075069, 67075067, 67075037, 67074947, 67074901, 67074859,
  67074853, 67074851, 67074829, 67074691, 67074619, 67074613, 67074611, 67074587,
  67074523, 67074467, 67074317, 67074307, 67074277, 67074269, 67074179, 67073947,
  67073917, 67073899, 67073803, 67073731, 67073707, 67073701, 67073683, 67073651,
  67073603, 67073597, 67073579, 67073533, 67073459, 67073387, 67073339, 67073333,
  67073323, 67073309, 67073261, 67073197, 67073189, 67073107, 67073051, 67073003,
  67072997, 67072979, 67072909, 67072877, 67072781, 67072757, 67072739, 67072693,
  67072541, 67072373, 67072363, 67072339, 67072309, 67072283, 67072277, 67072253,
  67072139, 67072037, 67071997, 67071989, 67071947, 67071923, 67071899, 67071883,
  67071877, 67071821, 67071707, 67071637, 67071547, 67071419, 67071413, 67071317,
  67071299, 67071293, 67071157, 67071149, 67071139, 67071061, 67070989, 67070981,
  67070909, 67070869, 67070837, 67070827, 67070813, 67070803, 67070749, 67070699,
  67070621, 67070573, 67070539, 67070459, 67070357, 67070317, 67070291, 67070261,
  67070251, 67070203, 67070053, 67070027, 67069979, 67069819, 67069813, 67069787,
  67069781, 67069763, 67069669, 67069661, 67069549, 67069531, 67069469, 67069427,
  67069397, 67069339, 67069157, 67069133, 67069109, 67069099, 67069043, 67069021,
  67068971, 67068931, 67068787, 67068653, 67068643, 67068629, 67068571, 67068557,
  67068539, 67068509, 67068493, 67068371, 67068301, 67068269, 67068259, 67068227,
  67068203, 67068187, 67068181, 67068173, 67068163, 67068101, 67067971, 67067933,
  67067909, 67067789, 67067779, 67067773, 67067723, 67067629, 67067597, 67067501,
  67067453, 67067437, 67067389, 67067387, 67067339, 67067293, 67067269, 67067213,
  67067173, 67067171, 67067069, 67067059, 67067029, 67066907, 67066861, 67066859,
  67066771, 67066757, 67066723, 67066709, 67066667, 67066619, 67066613, 67066379,
  67066277, 67066243, 67066211, 67066157, 67066093, 67066061, 67066019, 67065979,
  67065931, 67065917, 67065883, 67065827, 67065787, 67065667, 67065659, 67065653,
  67065643, 67065619, 67065563, 67065461, 67065437, 67065389, 67065373, 67065293,
  67065283, 67065227, 67065211, 67065157, 67065091, 67064843, 67064827, 67064819,
  67064773, 67064771, 67064741, 67064717, 67064693, 67064611, 67064597, 67064587,
  67064579, 67064549, 67064467, 67064299, 67064267, 67064237, 67064213, 67064197,
  67064171, 67064147, 67064131, 67064093, 67064059, 67063853, 67063813, 67063723,
  67063643, 67063637, 67063523, 67063517, 67063397, 67063349, 67063307, 67063189,
  67063163, 67063133, 67063123, 67063099, 67063093, 67063069, 67063043, 67063037,
  67063019, 67062923, 67062893, 67062883, 67062859, 67062659, 67062629, 67062613,
  67062539, 67062509, 67062469, 67062461, 67062379, 67062349, 67062299, 67062221,
  67062179, 67062157, 67062067, 67062029, 67062011, 67061987, 67061947, 67061933,
  67061909, 67061867, 67061861, 67061789, 67061747, 67061693, 67061627, 67061597,
  67061563, 67061531, 67061333, 67061299, 67061227, 67061219, 67061179, 67061173,
  67061147, 67061003, 67060997, 67060957, 67060949, 67060933, 67060837, 67060813,
  67060627, 67060549, 67060523, 67060517, 67060507, 67060451, 67060421, 67060373,
  67060333, 67060307, 67060277, 67060261, 67060229, 67060187, 67060171, 67060141,
  67060109, 67060067, 67060043, 67060027, 67060013, 67059989, 67059907, 67059899,
  67059869, 67059779, 67059757, 67059749, 67059731, 67059709, 67059701, 67059637,
  67059613, 67059581, 67059547, 67059533, 67059523, 67059437, 67059427, 67059259,
  67059173, 67059061, 67058963, 67058941, 67058909, 67058899, 67058891, 67058867,
  67058843, 67058723, 67058699, 67058669, 67058627, 67058531, 67058389, 67058347,
  67058339, 67058323, 67058309, 67058269, 67058227, 67058213, 67058141, 67058003,
  67057883, 67057853, 67057819, 67057813, 67057763, 67057733, 67057723, 67057717,
  67057709, 67057643, 67057499, 67057493, 67057387, 67057381, 67057379, 67057363,
  67057307, 67057147, 67057141, 67056989, 67056971, 67056917, 67056877, 67056763,
  67056677, 67056667, 67056659, 67056637, 67056611, 67056581, 67056461, 67056419,
  67056371, 67056259, 67056251, 67056179, 67056107, 67056083, 67056053, 67056043,
  67056013, 67055957, 67055909, 67055843, 67055789, 67055771, 67055629, 67055539,
  67055491, 67055477, 67055467, 67055347, 67055309, 67055299, 67055291, 67055267,
  67055243, 67055203, 67055179, 67055147, 67054997, 67054979, 67054907, 67054877,
  67054859, 67054763, 67054733, 67054717, 67054541, 67054523, 67054483, 67054411,
  67054387, 67054301, 67054213, 67054051, 67054037, 67053997, 67053971, 67053941,
  67053893, 67053787, 67053733, 67053659, 67053653, 67053643, 67053629, 67053619,
  67053563, 67053557, 67053523, 67053517, 67053419, 67053397, 67053373, 67053317,
  67053251, 67053229, 67053197, 67053179, 67053149, 67053037, 67053029, 67052963,
  67052939, 67052933, 67052819, 67052813, 67052779, 67052723, 67052677, 67052509,
  67052477, 67052467, 67052243, 67052021, 67051979, 67051949, 67051909, 67051883,
  67051861, 67051813, 67051811, 67051781, 67051709, 67051651, 67051643, 67051573,
  67051571, 67051547, 67051493, 67051379, 67051373, 67051331, 67051253, 67051189,
  67051181, 67051099, 67051069, 67051021, 67050979, 67050931, 67050917, 67050869,
  67050827, 67050749, 67050707, 67050701, 67050619, 67050611, 67050541, 67050509,
  67050443, 67050421, 67050419, 67050371, 67050301, 67050299, 67050251, 67050187,
  67050101, 67050077, 67049987, 67049981, 67049963, 67049909, 67049891, 67049867,
  67049837, 67049813, 67049747, 67049707, 67049693, 67049629, 67049627, 67049603,
  67049573, 67049539, 67049453, 67049413, 67049267, 67049261, 67049251, 67049179,
  67049149, 67049141, 67049093, 67049027, 67048963, 67048859, 67048819, 67048757,
  67048733, 67048693, 67048627, 67048621, 67048523, 67048469, 67048411, 67048349,
  67048277, 67048259, 67048141, 67048123, 67048109, 67047989, 67047859, 67047787,
  67047763, 67047749, 67047733, 67047731, 67047683, 67047619, 67047613, 67047611,
  67047581, 67047517, 67047509, 67047413, 67047397, 67047283, 67047131, 67047077,
  67047061, 67047059, 67047053, 67047037, 67047011, 67046989, 67046939, 67046899,
  67046797, 67046779, 67046731, 67046549, 67046531, 67046477, 67046467, 67046437,
  67046429, 67046411, 67046387, 67046363, 67046341, 67046333, 67046261, 67046197,
  67046107, 67046069, 67046059, 67046051, 67045973, 67045949, 67045907, 67045877,
  67045723, 67045613, 67045579, 67045571, 67045549, 67045541, 67045507, 67045403,
  67045339, 67045301, 67045267, 67045261, 67045211, 67045189, 67045133, 67045117,
  67045109, 67045061, 67045037, 67045019, 67044973, 67044907, 67044829, 67044797,
  67044779, 67044773, 67044763, 67044739, 67044541, 67044427, 67044371, 67044347,
  67044301, 67044283, 67044203, 67044157, 67044083, 67044077, 67044067, 67044053,
  67043981, 67043939, 67043909, 67043813, 67043797, 67043707, 67043507, 67043477,
  67043443, 67043243, 67043147, 67043107, 67043083, 67043069, 67043059, 67043051,
  67043027, 67042979, 67042973, 67042949, 67042931, 67042709, 67042643, 67042637,
  67042589, 67042571, 67042541, 67042523, 67042501, 67042453, 67042427, 67042363,
  67042307, 67042301, 67042259, 67042211, 67042091, 67042043, 67041907, 67041893,
  67041869, 67041797, 67041749, 67041731, 67041701, 67041613, 67041581, 67041563,
  67041547, 67041539, 67041509, 67041467, 67041461, 67041419, 67041371, 67041307,
  67041283, 67041269, 67041203, 67041187, 67041179, 67041043, 67040917, 67040893,
  67040789, 67040773, 67040723, 67040629, 67040627, 67040621, 67040587, 67040549,
  67040509, 67040443, 67040387, 67040381, 67040317, 67040291, 67040261, 67040243,
  67040219, 67040203, 67040069, 67040021, 67039997, 67039957, 67039883, 67039877,
  67039867, 67039853, 67039811, 67039757, 67039723, 67039699, 67039669, 67039627,
  67039613, 67039571, 67039547, 67039501, 67039499, 67039309, 67039307, 67039253,
  67039187, 67039139, 67039051, 67039003, 67038947, 67038941, 67038877, 67038869,
  67038827, 67038787, 67038739, 67038637, 67038589, 67038557, 67038539, 67038533,
  67038427, 67038371, 67038341, 67038299, 67038277, 67038221, 67038197, 67038173,
  67038149, 67038133, 67038131, 67038067, 67038029, 67038011, 67037843, 67037837,
  67037819, 67037797, 67037771, 67037723, 67037683, 67037627, 67037603, 67037563,
  67037483, 67037459, 67037429, 67037389, 67037261, 67037227, 67037213, 67037107,
  67037101, 67037053, 67036979, 67036909, 67036901, 67036877, 67036867, 67036843,
  67036819, 67036811, 67036747, 67036643, 67036589, 67036547, 67036507, 67036469,
  67036397, 67036379, 67036357, 67036259, 67036243, 67036187, 67036181, 67036157,
  67036093, 67036027, 67036019, 67035989, 67035949, 67035931, 67035901, 67035803,
  67035707, 67035659, 67035653, 67035643, 67035589, 67035499, 67035491, 67035469,
  67035413, 67035349, 67035347, 67035307, 67035277, 67035149, 67035107, 67035077,
  67034987, 67034819, 67034699, 67034683, 67034677, 67034477, 67034419, 67034381,
  67034339, 67034309, 67034293, 67034171, 67034117, 67034069, 67034021, 67033859,
  67033763, 67033741, 67033709, 67033699, 67033667, 67033619, 67033613, 67033597,
  67033541, 67033507, 67033469, 67033429, 67033403, 67033357, 67033331, 67033283,
  67033277, 67033229, 67033157, 67033117, 67033061, 67032997, 67032941, 67032811,
  67032803, 67032701, 67032661, 67032653, 67032613, 67032587, 67032541, 67032523,
  67032517, 67032491, 67032461, 67032451, 67032443, 67032421, 67032389, 67032349,
  67032347, 67032299, 67032221, 67032179, 67032101, 67031941, 67031933, 67031893,
  67031851, 67031819, 67031813, 67031749, 67031693, 67031509, 67031483, 67031443,
  67031429, 67031387, 67031243, 67031219, 67031203, 67031189, 67031149, 67031147,
  67031123, 67031101, 67031059, 67030963, 67030933, 67030907, 67030867, 67030853,
  67030757, 67030741, 67030739, 67030693, 67030669, 67030597, 67030517, 67030451,
  67030427, 67030333, 67030331, 67030181, 67030069, 67030013, 67029947, 67029931,
  67029923, 67029917, 67029901, 67029811, 67029779, 67029763, 67029749, 67029709,
  67029707, 67029581, 67029541, 67029509, 67029491, 67029451, 67029437, 67029427,
  67029421, 67029373, 67029341, 67029323, 67029293, 67029269, 67029253, 67029229,
  67029077, 67029059, 67029043, 67029013, 67028981, 67028917, 67028771, 67028669,
  67028653, 67028651, 67028597, 67028557, 67028539, 67028477, 67028413, 67028387,
  67028243, 67028197, 67028083, 67028069, 67028021, 67027997, 67027963, 67027949,
  67027931, 67027867, 67027861, 67027811, 67027693, 67027627, 67027619, 67027547,
  67027507, 67027453, 67027427, 67027339, 67027283, 67027237, 67027189, 67027187,
  67027069, 67027027, 67027019, 67027013, 67026979, 67026907, 67026829, 67026811,
  67026803, 67026787, 67026643, 67026613, 67026539, 67026469, 67026467, 67026451,
  67026437, 67026403, 67026307, 67026299, 67026227, 67026187, 67026139, 67026131,
  67026109, 67026107, 67026083, 67026067, 67025971, 67025963, 67025957, 67025843,
  67025779, 67025773, 67025723, 67025701, 67025683, 67025669, 67025579, 67025573,
  67025531, 67025501, 67025459, 67025411, 67025363, 67025219, 67025213, 67025173,
  67025107, 67025051, 67025029, 67024987, 67024957, 67024901, 67024891, 67024733,
  67024637, 67024621, 67024613, 67024499, 67024483, 67024429, 67024411, 67024339,
  67024157, 67024141, 67024003, 67023989, 67023899, 67023893, 67023779, 67023763,
  67023667, 67023653, 67023493, 67023443, 67023421, 67023419, 67023371, 67023349,
  67023347, 67023331, 67023293, 67023259, 67023227, 67023211, 67023179, 67023157,
  67023139, 67023133, 67023091, 67023059, 67023053, 67023043, 67023037, 67023029,
  67022869, 67022819, 67022797, 67022723, 67022707, 67022701, 67022699, 67022693,
  67022539, 67022507, 67022477, 67022467, 67022387, 67022261, 67022243, 67022237,
  67022213, 67022147, 67022077, 67022027, 67021979, 67021963, 67021901, 67021861,
  67021741, 67021739, 67021723, 67021637, 67021621, 67021613, 67021499, 67021469,
  67021459, 67021363, 67021301, 67021237, 67021147, 67021139, 67021099, 67021067,
  67021043, 67020979, 67020973, 67020917, 67020893, 67020869, 67020797, 67020763,
  67020683, 67020589, 67020587, 67020557, 67020491, 67020397, 67020323, 67020299,
  67020251, 67020179, 67020077, 67020053, 67020013, 67019963, 67019867, 67019837,
  67019819, 67019747, 67019741, 67019653, 67019587, 67019549, 67019483, 67019437,
  67019371, 67019299, 67019123, 67019077, 67019027, 67019003, 67018997, 67018843,
  67018837, 67018771, 67018733, 67018717, 67018667, 67018613, 67018499, 67018493,
  67018429, 67018397, 67018387, 67018309, 67018181, 67018163, 67018141, 67018139,
  67018069, 67018051, 67017971, 67017931, 67017803, 67017763, 67017733, 67017707,
  67017677, 67017661, 67017659, 67017571, 67017563, 67017547, 67017413, 67017371,
  67017299, 67017277, 67017227, 67017211, 67017163, 67017157, 67017107, 67017059,
  67016869, 67016821, 67016813, 67016723, 67016717, 67016707, 67016693, 67016627,
  67016611, 67016483, 67016437, 67016387, 67016269, 67016197, 67016189, 67016179,
};

static inline
int get_next_lower_prime(int current_prime){
    bool is_prime = false;

    int i;
    CGAL_precondition_msg(current_prime != 2 ," primes definitely exhausted ");

    if((current_prime <= 7) && (current_prime > 2)){
        if(current_prime <= 5){
            if(current_prime == 3)
                return 2;
            return 3;
        }
        return 5;
    }
    for(i=current_prime-2;(i>1 && !is_prime);i=i-2){
        int r = 1;
        for(int j=3; (j <= i/2 && (r != 0)); j++){
            r = i % j;
//                std::cout<<"i " <<i<<std::endl;
//                std::cout<<"j " <<j<<std::endl;
//                std::cout<<"i%j " <<i%j<<std::endl;
            if(j==i/2 && r != 0)
                is_prime = true;
        }
    }
//    CGAL_precondition_msg(is_prime," primes definitely exhausted ");
    return i+2;
}


}
}

#endif // CGAL_PRIMES_H
