;Author: Byung Lee

(defprotocol Change
	"A protocol for change"
	(move [_ distance] "Move") 
	(left [_] "left")
	(right [_] "right"))

(defrecord Robot [x y direction]
	Change
	(move [this distance] ;this is an object itself
		(cond 
			(= :e direction) (assoc this :x (+ x distance))
			(= :n direction) (assoc this :y (+ y distance))
			(= :w direction) (assoc this :x (- x distance))
			(= :s direction) (assoc this :y (- y distance))
			:else "Wrong direction"))
	(left [this] 
		(cond 
			(= :e direction) (assoc this :direction :n)
			(= :n direction) (assoc this :direction :w)
			(= :w direction) (assoc this :direction :s)
			(= :s direction) (assoc this :direction :e)
			:else "Wrong direction"))
	(right [this]
		(cond 
			(= :e direction) (assoc this :direction :s)
			(= :n direction) (assoc this :direction :e)
			(= :w direction) (assoc this :direction :n)
			(= :s direction) (assoc this :direction :w)
			:else "Wrong direction"))

	)

;Helper function to rotate
(defn rotate [n string]
  (let [at (mod (* -1 n) (count string))  
        [newtail newhead] (split-at at string)]
    (apply str (concat newhead newtail))))

(extend-type String
	Change
	(move [this distance] (rotate distance this))
	(left [this] (rotate -1 this))
	(right [this] (rotate 1 this)))
