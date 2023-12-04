const tokens = {
    day1: "⭐",
    day2: "🌟"
}
// test: git log --all --since='Dec-1-2022' --grep='[⭐🌟]' --no-merges --format=author:%an%n%s
const git_cmd = `log --all --since='Dec-1-2022' --grep='[${tokens.day1}${tokens.day2}]' --no-merges --format=author:%an%n%s`
const repo = new Deno.Command('git', {
    args: git_cmd.split(" "),
    stdout: "piped",
    stderr: "piped"
})

const { code, stdout, stderr } = repo.outputSync();

const out = new TextDecoder().decode(stdout)
for (let line of out) {
    console.log(line)
}
console.log(new TextDecoder().decode(stdout))
console.log(new TextDecoder().decode(stderr))
