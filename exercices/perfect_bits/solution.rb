## determine the number of of base-64 integers between a and b
## that when written in binary, have a perfect-square number of 1's
def perfect_bits(a, b)
  ordered = [a,b].sort
  return pb(ordered.last) - pb(ordered.first-1)
end

## number of groups of size k we can form from n elements
## (number of ways we can put k 1's into n bits)
def choose(n, k)
  return 1 if k == 0
  return 0 if n == 0
  return (n * choose(n-1, k-1)) / k
end

## number of ways to rearrange b bits into a number <= n
def combos(n, b)
  return 0 if n <= 0

  binary = n.to_s(2) # has a leading 1

  return binary.length if b == 1
  return 0 if binary.length < b

  return 1 if binary.length == b && binary =~ /^1*$/
  total = choose(binary.length - 1, b)
  n == 1 ? total : total + combos(binary[1..-1].to_i(2), b-1)
end

## number of perfect_bit numbers between 1 and a (inclusive)
def pb(a)
  return 0 if a <= 0

  binary = a.to_s(2)
  n = binary.length

  sqrt_n = Math.sqrt(n).floor
  total = 0

  (1..sqrt_n).each do |i|
    total += combos(a, i*i)
  end

  total
end


if ARGV.length != 2
  puts "Usage: #{$0} a b"
  exit 1
end

puts perfect_bits(ARGV[0].to_i, ARGV[1].to_i)
#puts pb(ARGV[0].to_i)
#puts pb(ARGV[1].to_i)