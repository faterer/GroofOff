package main

import "fmt"
import "os"

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce medicine!
 **/

func GoAndConnect(module string, data interface{}, position string) {
	if module == position {
		fmt.Println("CONNECT", data)
	} else {
		fmt.Println("GOTO", module)
	}
}

func sum(array [5]int) int {
	sum := 0
	for i := 0; i < 5; i++ {
		sum = sum + array[i]
	}
	return sum
}

type Robot struct {
	target     string
	eta        int
	score      int
	storage    [5]int
	expertise  [5]int
	availableM [5]int
	carrying   []Sample
}

type Sample struct {
	sampleId      int
	carriedBy     int
	rank          int
	expertiseGain string
	health        int
	cost          [5]int
	diagnosed     bool
}

func TakeSample(robots []Robot) {
	//take three samples
	if len(robots[0].carrying) < 3 {
		if sum(robots[0].expertise) < 8 {
			GoAndConnect("SAMPLES", 2, robots[0].target)
		} else {
			GoAndConnect("SAMPLES", 3, robots[0].target)
		}
	} else {
		fmt.Println("GOTO DIAGNOSIS")
	}
}

func DiagnosisSample(robots []Robot) {
	var sampleCount int
	//diagnose samples
	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
		sample := robots[0].carrying[sampleCount]
		if sample.diagnosed {
			//if cost is more than available, transfer sample to cloud
			for i := 0; i < 5; i++ {
				if sample.cost[i]-robots[0].expertise[i] > 5 {
					GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
					break
				}
			}
		} else {
			GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
			break
		}
	}

	fmt.Fprintln(os.Stderr, sampleCount)

	if sampleCount == len(robots[0].carrying) {
		fmt.Println("GOTO MOLECULES")
	}
}

func GetMolecules(robots []Robot) {
	var sampleCount int

	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
		sample := robots[0].carrying[sampleCount]
	}
}

func main() {
	var projectCount int
	fmt.Scan(&projectCount)

	for i := 0; i < projectCount; i++ {
		var a, b, c, d, e int
		fmt.Scan(&a, &b, &c, &d, &e)
		fmt.Fprintln(os.Stderr, a, b, c, d, e)
	}

	for {
		var robot Robot
		var robots []Robot
		for i := 0; i < 2; i++ {
			var target string
			var eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseE int
			fmt.Scan(&target, &eta, &score, &storageA, &storageB, &storageC, &storageD, &storageE, &expertiseA, &expertiseB, &expertiseC, &expertiseD, &expertiseE)
			robot.target = target
			robot.eta = eta
			robot.score = score
			robot.storage = [5]int{storageA, storageB, storageC, storageD, storageE}
			robot.expertise = [5]int{expertiseA, expertiseB, expertiseC, expertiseD, expertiseE}
			robots = append(robots, robot)
		}

		var availableA, availableB, availableC, availableD, availableE int
		fmt.Scan(&availableA, &availableB, &availableC, &availableD, &availableE)
		robots[0].availableM = [5]int{availableA, availableB, availableC, availableD, availableE}

		var sampleCount int
		fmt.Scan(&sampleCount)
		var sample Sample
		fmt.Fprintln(os.Stderr, robots[0])
		fmt.Fprintln(os.Stderr, robots[1])

		for i := 0; i < sampleCount; i++ {
			var sampleId, carriedBy, rank int
			var expertiseGain string
			var health, costA, costB, costC, costD, costE int
			fmt.Scan(&sampleId, &carriedBy, &rank, &expertiseGain, &health, &costA, &costB, &costC, &costD, &costE)
			sample.sampleId = sampleId
			sample.carriedBy = carriedBy
			sample.rank = rank
			sample.expertiseGain = expertiseGain
			sample.health = health
			sample.cost = [5]int{costA, costB, costC, costD, costE}
			sample.diagnosed = (health != -1)
			fmt.Fprintln(os.Stderr, sample)
			if carriedBy > -1 {
				robots[carriedBy].carrying = append(robots[carriedBy].carrying, sample)
			}
		}

		if robots[0].eta > 0 {
			fmt.Println("")
		} else {
			//funcation code as below
			switch robots[0].target {
			case "START_POS":
				fmt.Println("GOTO SAMPLES")
				break
			case "SAMPLES":
				//take samples
				TakeSample(robots)
				//fmt.Println("GOTO DIAGNOSIS")
				break
			case "DIAGNOSIS":
				DiagnosisSample(robots)
				break
			case "MOLECULES":
				GetMolecules(robots)
				fmt.Println("GOTO LABORATORY")
				break
			case "LABORATORY":
				fmt.Println("GOTO SAMPLES")
				break
			}
		}
		/*

		   if len(robots[0].carrying) < 3 && !produceCompleted {
		       if sum(robots[0].expertise) < 8 {
		           GoAndConnect("SAMPLES", 2, robots[0].target)
		       } else {
		           GoAndConnect("SAMPLES", 3, robots[0].target)
		       }
		   } else {
		       if len(robots[0].carrying) == 0 {
		           produceCompleted = false
		           GoAndConnect("SAMPLES", 2, robots[0].target)
		       } else {

		           if !robots[0].carrying[0].diagnosed {
		               GoAndConnect("DIAGNOSIS", robots[0].carrying[0].sampleId, robots[0].target)
		           } else if len(robots[0].carrying) > 1 && !robots[0].carrying[1].diagnosed {
		               GoAndConnect("DIAGNOSIS", robots[0].carrying[1].sampleId, robots[0].target)
		           } else if len(robots[0].carrying) > 2 && !robots[0].carrying[2].diagnosed {
		               GoAndConnect("DIAGNOSIS", robots[0].carrying[2].sampleId, robots[0].target)
		           } else {
		               notAvail := false
		               cantProduce := false
		               sample = robots[0].carrying[0]
		               for j := 0;j < 5 ;j++ {
		                   if robots[0].carrying[0].cost[j] - robots[0].expertise[j] > 5 {
		                       cantProduce = true
		                       break
		                   }
		               }

		               if cantProduce {
		                   GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
		               } else {
		                   var neededMolecule string
		                   for j := 0; j < 5; j++ {
		                       if robots[0].storage[j] < sample.cost[j] - robots[0].expertise[j] {
		                           if robots[0].availableM[j] == 0 {
		                               notAvail = true
		                           }
		                           neededMolecule = string("ABCDE"[j])
		                           break
		                       }
		                   }

		                   if neededMolecule != "" {
		                       if notAvail {
		                           fmt.Println("WAIT")
		                       } else {
		                           GoAndConnect("MOLECULES", neededMolecule, robots[0].target)
		                       }
		                   } else {
		                       if robots[0].target == "LABORATORY" {
		                           produceCompleted = true
		                       }
		                       GoAndConnect("LABORATORY", sample.sampleId, robots[0].target)
		                   }
		               }
		           }
		       }
		   }
		*/
	}
}
