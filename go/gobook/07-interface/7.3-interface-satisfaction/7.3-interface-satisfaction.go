package satisfies

func main() {
	var w io.Writer
	w = os.Stdout //OK: *os.File has Write method
	w = new(bytes.Buffer) //OK: *bytes.Buffer has Write method
	w = time.Second // compile error: time.Duration lacks Write method

	var rwc io.ReadWriteCloser
	rwc = os.Stdout //OK: *os.File has Read, Write, Close methods
	rwc = new(bytes.Buffer) //compile error: *bytes.Buffer lacks Close method

}

type IntSet struct { /* ... */ }
func (*IntSet) String() string
var _ = IntSet{}.String() // compile error: String requires *IntSet receiver

var s IntSet
var _ = s.String() //OK: s is a variable and &s has a String method

//since only *IntSet has a String method, only *IntSet satifies the fmt.Stringer interface
var _ fmt.Stringer = &s //ok
var _ fmt.Stringer = s //compile error: IntSet lacks a String method

os.Stdout.Write([]byte("hello")) //OK: *os.File has Write method
os.Stdout.Close()	//OK: *os.File has Close method

var w io.Writer
w = os.Stdout
w.Write([]byte("hello")) //OK: io.Writer has Write method
w.Close()	//compile error: io.Writer lacks Close method

//empty interface
var any interface{}
any = true
any = 3.14
any = "hello"
any = map[string]int{"one":1}
any = new(bytes.Buffer)

// *bytes.Buffer must satisfy io.Writer
var w io.Writer = new(bytes.Buffer)

// *bytes.Buffer must satisfy io.Writer
var _ io.Writer = bytes.Buffer(nil)

type Artifact interface {
	Title() string
	Creators() []string
	Created() time.Time
}

type Text interface {
	Pages() int
	Words() int
	PageSize() int
}

type Audio interface {
	Stream() (io.ReadCloser, error)
	RunningTime() time.Duration
	Format() string //e.g., "MP3", "WAV"
}

type Video interface {
	Stream() (io.ReadCloser, error)
	RunningTime() time.Duration
	Format() string //e.g., "MP4", "WMV"
	Resolution() (x, y int)
} 

type Streamer interface {
	Stream() (io.ReadCloser, error)
	RunningTime() time.Duration
	Format() string
}