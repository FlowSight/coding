// There will be m module. you have to refactor those modules and also need to release. To refactor each module require specific amount of days.

// refactor = [2, 2]

// where first module takes 2 days and second module takes 2 days.

// There will be another arrays n sizes

// schedule = [0, 0, 1, 2, 2, 2, 0, 1, 2]

// which if schedule[i] = 0 means you cant release but you can refactor/skip

// if shcedule[i] > 0 can refactor/skip/release. but to release only specified module can be released.

// Now you have to find out what is the minimum of days required to release all module if not possible returns -1.

// Note:

// module needs to be refactored before release
// at a single day only one module can be released/refactored
// Explanation:
// 1st module will be refactored on 1st, 2nd days and release will be on 3rd days
// 2nd module will be refactored on 4th, 5th days and release will be 6th days

// so answer is 6