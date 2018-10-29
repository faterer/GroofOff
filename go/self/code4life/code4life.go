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
	sps        [][5]int
	carrying   []Sample
	incloud    []Sample
}

type Sample struct {
	sampleId        int
	carriedBy       int
	rank            int
	expertiseGain   string
	health          int
	cost            [5]int
	diagnosed       bool	
}

func CollectSample(robots []Robot) {
    var sampleCount int
    var moleculeCount int
    var sampleInCloud int
    
	//check if can take sample from cloud and 
    for sampleCount = 0; sampleCount < len(robots[0].incloud); sampleCount++ {
        sample := robots[0].incloud[sampleCount]
        //fmt.Fprintln(os.Stderr, sample)
    	for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
			if sample.cost[moleculeCount] - robots[0].expertise[moleculeCount] - robots[0].storage[moleculeCount] > robots[0].availableM[moleculeCount] {
                break
			}
    	}
    	
    	if robots[1].target == "DIAGNOSIS" || robots[1].target == "MOLECULES" {
    	    break
    	}
    	
    	if moleculeCount == 5 {
        	for i := 0; i < len(robots[0].sps); i++ {
                sp := robots[0].sps[i]
                if sp[0] > 0 && sample.expertiseGain == string("ABCDE"[0]) {
                    sampleInCloud += 1
                    break
                } else if sp[1] > 0 && sample.expertiseGain == string("ABCDE"[1]) {
                    sampleInCloud += 1
                    break
                } else if sp[2] > 0 && sample.expertiseGain == string("ABCDE"[2]) {
                    sampleInCloud += 1
                    break
                } else if sp[3] > 0 && sample.expertiseGain == string("ABCDE"[3]) {
                    sampleInCloud += 1
                    break
                } else if sp[4] > 0 && sample.expertiseGain == string("ABCDE"[4]) {
                    sampleInCloud += 1
                    break
                }
            }
    	}
    }
    
	//take three samples
	sampleCount = len(robots[0].carrying) + sampleInCloud
	if sampleCount < 3 {	    
		if sum(robots[0].expertise) <= 5  {
			GoAndConnect("SAMPLES", 1, robots[0].target)
		} else if sum(robots[0].expertise) <= 10 {
		    if sampleCount < 2 {
		        GoAndConnect("SAMPLES", 2, robots[0].target)
		    } else {
		        GoAndConnect("SAMPLES", 1, robots[0].target) 
		    }
		} else if sum(robots[0].expertise) <= 14 {
		    if sampleCount < 2 {
		        GoAndConnect("SAMPLES", 3, robots[0].target)
		    } else {
		        GoAndConnect("SAMPLES", 2, robots[0].target) 
		    }
		} else {
		    GoAndConnect("SAMPLES", 3, robots[0].target)
		}
	} else {
		fmt.Println("GOTO DIAGNOSIS")
	}
}

func AnalyzeSample(robots []Robot) {
	var sampleCount int
	var moleculeCount int

    //no sample and go to samples
	if len(robots[0].carrying) == 0 {
	    fmt.Println("GOTO SAMPLES")
	    return
	}

	//take samples and diagnose samples
	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
		sample := robots[0].carrying[sampleCount]
		if !sample.diagnosed {
			GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
			return
		}
	}
	
	//if cost is more than available, transfer sample to cloud	
    for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
		sample := robots[0].carrying[sampleCount]
		
		if robots[1].target == "MOLECULES" || robots[1].target == "LABORATORY" {
		    break
		}
		
		for i := 0; i < 5; i++ {
			if sample.cost[i] - robots[0].expertise[i] - robots[0].storage[i] > robots[0].availableM[i] {
				GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
				return
			}
		}
	}
	
	//check if can take sample from cloud
	if len(robots[0].carrying) < 3 {
	    for sampleCount = 0; sampleCount < len(robots[0].incloud); sampleCount++ {
	        sample := robots[0].incloud[sampleCount]
	        fmt.Fprintln(os.Stderr, sample)
	    	for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
				if sample.cost[moleculeCount] - robots[0].expertise[moleculeCount] - robots[0].storage[moleculeCount] > robots[0].availableM[moleculeCount] {
                    break
				}
	    	}
	    	
	    	if moleculeCount == 5 {
	    	    GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
	    	    return
	    	}
	    }
	}
	
	//sample take and molecules take enough, go to LABORATORY
	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
	    sample := robots[0].carrying[sampleCount]
		for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
		    if (robots[0].storage[moleculeCount] < sample.cost[moleculeCount] - robots[0].expertise[moleculeCount]) {
                break
		    }
		}
		
        if moleculeCount == 5 && sampleCount == len(robots[0].carrying) {
            fmt.Println("GOTO LABORATORY")
            return
        }
	}
	
	if len(robots[0].carrying) <= 1 {
        fmt.Println("GOTO SAMPLES")
	    return	    
	}
	
	//take enough samples go to molecules
	if len(robots[0].carrying) == sampleCount {
	    fmt.Println("GOTO MOLECULES")
	    return
	}
}

func GatherMolecules(robots []Robot) {
	var sampleCount int
    var moleculeCount int
     
    //gather the more molecules the better
	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
	  
		//sampleCount == 0
		if sampleCount == 0 {
		    sample0 := robots[0].carrying[0]
            fmt.Fprintln(os.Stderr, sample0)
    		for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
    		    if (robots[0].storage[moleculeCount] < sample0.cost[moleculeCount] - robots[0].expertise[moleculeCount]) &&
    		        (robots[0].availableM[moleculeCount] > 0) &&
    		        (sum(robots[0].storage) < 10) {
    		        GoAndConnect("MOLECULES", string("ABCDE"[moleculeCount]), robots[0].target)
                    return
    		    }
    		}
		} else if sampleCount == 1 {
		    sample0 := robots[0].carrying[0]
		    sample1 := robots[0].carrying[1]
		    for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
		        //sample0 cost
		        prevSamplesCost := 0
		        if sample0.cost[moleculeCount] > robots[0].expertise[moleculeCount] {
		            prevSamplesCost = sample0.cost[moleculeCount] - robots[0].expertise[moleculeCount]
		        }
		        
    		    if (robots[0].storage[moleculeCount] - prevSamplesCost < sample1.cost[moleculeCount] - robots[0].expertise[moleculeCount]) &&
    		        (robots[0].availableM[moleculeCount] > 0) &&
    		        (sum(robots[0].storage) < 10) {
    		        GoAndConnect("MOLECULES", string("ABCDE"[moleculeCount]), robots[0].target)
                    return
    		    }
    		}    	
		} else if sampleCount == 2 {
			sample0 := robots[0].carrying[0]
		    sample1 := robots[0].carrying[1]
		    sample2 := robots[0].carrying[2]
		    for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
		        //sample0 cost
		        prevSamplesCost := 0
	            if sample0.cost[moleculeCount] > robots[0].expertise[moleculeCount] {
		            prevSamplesCost = sample0.cost[moleculeCount] - robots[0].expertise[moleculeCount]
		        } 
		        //sample1 cost
	            if sample1.cost[moleculeCount] > robots[0].expertise[moleculeCount] {
		            prevSamplesCost = prevSamplesCost + sample1.cost[moleculeCount] - robots[0].expertise[moleculeCount]
		        }	   	        
		  
    		    if (robots[0].storage[moleculeCount] - prevSamplesCost < sample2.cost[moleculeCount] - robots[0].expertise[moleculeCount]) &&
    		        (robots[0].availableM[moleculeCount] > 0) &&
    		        (sum(robots[0].storage) < 10) {
    		        GoAndConnect("MOLECULES", string("ABCDE"[moleculeCount]), robots[0].target)
                    return
    		    }
    		} 
		}
	}		
	
	//check molecules is enough and go to laboratory
	for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
	    sample := robots[0].carrying[sampleCount]
		for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
		    if (robots[0].storage[moleculeCount] < sample.cost[moleculeCount] - robots[0].expertise[moleculeCount]) {
                break
		    }
		}
		
        if moleculeCount == 5 {
            fmt.Println("GOTO LABORATORY")
            return
        }
	}
	
	//go to samples or go to diagnosis
	if len(robots[0].carrying) < 3 {
	    /*
	    //check if can take sample from cloud
	    for sampleCount = 0; sampleCount < len(robots[0].incloud); sampleCount++ {
	        sample := robots[0].incloud[sampleCount]
	        fmt.Fprintln(os.Stderr, sample)
	    	for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
				if sample.cost[moleculeCount] - robots[0].expertise[moleculeCount] - robots[0].storage[moleculeCount] > robots[0].availableM[moleculeCount] {
                    break
				}
	    	}
	    	
	    	if moleculeCount == 5 {
	    	    GoAndConnect("DIAGNOSIS", sample.sampleId, robots[0].target)
	    	    return
	    	}
	    }  
	    */
	    fmt.Println("GOTO SAMPLES")
	} else {	
	    fmt.Println("GOTO DIAGNOSIS")
	}
}

func ProduceMedicines(robots []Robot) {
    var sampleCount int
    var moleculeCount int
    
    //produce medicines
    for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
        sample := robots[0].carrying[sampleCount]
		for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
		    if (robots[0].storage[moleculeCount] < sample.cost[moleculeCount] - robots[0].expertise[moleculeCount]) {
                break
		    }
		}
		
        if moleculeCount == 5 {
            GoAndConnect("LABORATORY", sample.sampleId, robots[0].target)
            return
        }
    }
    
    
    if len(robots[0].carrying) <= 1 {       
        for sampleCount = 0; sampleCount < len(robots[0].carrying); sampleCount++ {
	        sample := robots[0].carrying[sampleCount]
	        //fmt.Fprintln(os.Stderr, sample)
	    	for moleculeCount = 0; moleculeCount < 5; moleculeCount++ {
				if sample.cost[moleculeCount] - robots[0].expertise[moleculeCount] - robots[0].storage[moleculeCount] > robots[0].availableM[moleculeCount] {
                    break
				}
	    	}
	    	
	    	if moleculeCount == 5 {
	    	    fmt.Println("GOTO MOLECULES")
	    	    return
	    	}
	    }
	    
        fmt.Println("GOTO SAMPLES")
        return
    }
    

    fmt.Println("GOTO MOLECULES")
}

func main() {
	var projectCount int
	fmt.Scan(&projectCount)
    var sps [][5]int
    
	for i := 0; i < projectCount; i++ {
		var a, b, c, d, e int
		fmt.Scan(&a, &b, &c, &d, &e)
		
		sp := [5]int{a, b, c, d, e}
		sps = append(sps, sp)
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
		robots[0].sps = sps
		//fmt.Fprintln(os.Stderr, robots[0].sps[0][0])

		var sampleCount int
		fmt.Scan(&sampleCount)
		var sample Sample

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
			
			if carriedBy > -1 {
				robots[carriedBy].carrying = append(robots[carriedBy].carrying, sample)	
			}
			
			if carriedBy == -1 {
			    robots[0].incloud = append(robots[0].incloud, sample)
			    fmt.Fprintln(os.Stderr, sample)
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
				CollectSample(robots)
				break
			case "DIAGNOSIS":
				AnalyzeSample(robots)
				break
			case "MOLECULES":
				GatherMolecules(robots)
				break
			case "LABORATORY":
				ProduceMedicines(robots)
				break
			}
		}
	}
}